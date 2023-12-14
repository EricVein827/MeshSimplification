#include "Simplification.h"

Simplification::Simplification(const string& _modelName)
{
	modelName = _modelName;
	ratio = 0.5;
	
	model = new BaseModel(modelName);

	eHeap = new Heap();
	cntFace = 0;
	cntVertex = 0;
}

Simplification::~Simplification(void)
{
	delete model;
	delete eHeap;
	cntFace = 0;
	cntVertex = 0;
	ratio = 0;
}

void Simplification::setRatio(const double& _ratio)
{
	ratio = _ratio;
}

void Simplification::initialize()
{
	vector<Eigen::Matrix4d> MF = model->getVectorMatrix(); // the matrix for faces
	MXi F = model->getFace();
	MXd V = model->getVert();
	MXd N = model->getNormal();
	cntFace = F.rows();
	cntVertex = V.rows();
	vector<vector<int >> one_ringF = model->getOneRingF();

	for (int i = 0; i < cntFace; i++)
	{
		fGroup.emplace_back(Face(F.row(i), N.row(i), MF[i]));
	}

	vector<Eigen::Matrix4d> MV; //  restore the matrix Q of each vertex


	for (int i = 0; i < cntVertex; i++)
	{
		//cout << "i  =    " << i << endl;
		Vertex v(i, V.row(i), one_ringF);
		v.setAdjacentV(F);
		//cout << v.getQ(MF) << endl;
		MV.emplace_back(v.getQ(MF)); // compute Q of each vertex and restore it to MV
		vGroup.emplace_back(v);
	}

	// add edges to  heap
	vector<V2i> E = model->getEdge(); // the edges of the input model

//#pragma omp parallel for
	for (int i = 0; i < E.size(); i++)
	{
		const V2i& e = E[i];
		Edge edge(e.x(), e.y());
		edge.calCostAndV(MV, one_ringF, V);
		//cout << "cost =  " << edge.cost << "     constraction position = " << edge.V.transpose() << endl;
		eHeap->addEdge(edge);
	}
}

void Simplification::simplify()
{
	// the number of left faces after simplification
	int cntDelFace = static_cast<int>((1 - ratio) * cntFace);
	//cout << "all = " << cntDelFace << endl;

//#pragma omp parallel for // 单层循环, 循环变量必须得是有符号整数类型
////#pragma omp collapse // 多层循环
//#pragma omp critical
//	{
//		// 阻塞其他线程, 保证该代码块只会有一个线程执行, 其他线程必须等待
//	}
//#pragma omp barrier
//	{
//		// 设立一个栅栏, 用来同步所有线程
//	}
	for (int step = 0; step < cntDelFace; step += 2)
	{
		//cout << step << endl;
		Edge e = eHeap->getMinEdge(); 

		// delete e's edges
		vGroup[e.v1].isDeleted = true;
		vGroup[e.v2].isDeleted = true;
		eHeap->delEdge(e);   //label e with deleted
		
		set<int> connectV;   // the conneected verts with Edge e
		connectV.clear();
		 
		Vertex v1 = vGroup[e.v1];
		Vertex v2 = vGroup[e.v2];

		// delete v1, v2's adjacent faces
		for (const int& i : v1.adjacent_f) fGroup[i].isDeleted = true;
		for (const int& i : v2.adjacent_f) fGroup[i].isDeleted = true;

		for (const int& i: v1.adjacent_v) 
		{
			if (i != v2.id) 
			{
				eHeap->delEdge(Edge(i, v1.id));        //label Edge(i, v1.id) with deleted
				vGroup[i].adjacent_v.erase(v1.id);     // delete v1 from the connected verts' one-ring set
				connectV.insert(i);                    // add v_i to the constraction point's neighbor

				// delete i's adjacent face id
				set<int> tempset = vGroup[i].adjacent_f;
				for (const int& j : tempset)
				{
					if (fGroup[j].isDeleted) vGroup[i].adjacent_f.erase(j);
				}
			}
		}

		for (const int& i : v2.adjacent_v) 
		{
			if (i != v1.id) 
			{
				eHeap->delEdge(Edge(i, v2.id));        //label Edge(i, v2.id) with deleted
				vGroup[i].adjacent_v.erase(v2.id);     // delete v2 from the connected verts' one-ring set
				connectV.insert(i);                    // add v_i to the constraction point's neighbor

				// delete i's adjacent face id
				set<int> tempset = vGroup[i].adjacent_f;
				for (const int& j : tempset)
				{
					if (fGroup[j].isDeleted) vGroup[i].adjacent_f.erase(j);
				}
			}
		}

		// add new vertex to vertex group
		int newID = cntVertex++;
		Vertex v(newID, e.V);
		v.adjacent_v = connectV;
		
		vGroup.emplace_back(v);

		// add new faces
		for (const int& i : connectV)
		{
			for (const int& j : connectV)
			{
				if (i < j && vGroup[i].adjacent_v.count(j) > 0)  // if vi connects to vj 
				{
					Face tempF(i, j, newID);
					tempF.calQ(vGroup);
					fGroup.emplace_back(tempF);

					int fID = cntFace++;
					vGroup[newID].adjacent_f.insert(fID);
					vGroup[i].adjacent_f.insert(fID);
					vGroup[j].adjacent_f.insert(fID);
				}
			}

			// add new vertex to e's neighbors' adjacent v
			vGroup[i].adjacent_v.insert(newID);
		}

		// update adjacent vertex matrix
		for (const int& i : connectV)
		{
			for (const int& j : vGroup[i].adjacent_f)
			{
				vGroup[i].Q = vGroup[i].Q + fGroup[j].Q;
			}
		}
		// calculate Q at new v
		for (const int& i : vGroup[newID].adjacent_f)
		{
			vGroup[newID].Q = vGroup[newID].Q + fGroup[i].Q;
		}

		//add new Edges to Heap
		for (const int& i : connectV) 
		{
			Edge e(i, newID);
			e.calCostAndV(vGroup[i], vGroup[newID]);
			eHeap->addEdge(e);
		}
	}
}

void Simplification::output()const
{
	vector<V3d> outVerts;
	map<int, int> map4id;
	vector<V3i> outFaces;

	int cntV = 0;
	for (const Vertex& v : vGroup)
	{
		if (!v.isDeleted)
		{
			map4id[v.id] = cntV;
			outVerts.emplace_back(v.position);
			cntV++;
		}
	}

	for (const Face& f: fGroup) 
	{
		if (!f.isDeleted)
		{
			outFaces.emplace_back(V3i(map4id[f.F.x()], map4id[f.F.y()], map4id[f.F.z()]));
		}
	}

	MXi F(outFaces.size(), 3);
	MXd V(outVerts.size(), 3);
	for (int i = 0; i < outFaces.size(); i++) F.row(i) = outFaces[i];
	for (int i = 0; i < outVerts.size(); i++) V.row(i) = outVerts[i];
	igl::writeOBJ("..//output//" + modelName, V, F);
}
