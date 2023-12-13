#include "Simplification.h"

Simplification::Simplification(const string& modelName)
{
	model = new BaseModel(modelName);

	eHeap = new Heap();
	cntFace = 0;
}

Simplification::~Simplification(void)
{
	delete model;
	delete eHeap;
	cntFace = 0;
}

void Simplification::setRatio(const double& _ratio)
{
	ratio = _ratio;
}

void Simplification::initialize()
{
	
	vector<Eigen::Matrix4d> MV; //  restore the matrix Q of each vertex

	// add vertices to vertex group
	cntFace = model->_F.rows();

	// set FaceGroup
	for (int i = 0; i < cntFace; i++)
	{
		fGroup.emplace_back(FaceGroup(model->_F.row(i), model->_N.row(i)));
	}

	cntVertex = model->_V.rows(); // the original vertex number 
	vector<Eigen::Matrix4d> MF = model->_K; // the matrix for faces
	vector<vector<int >> one_ringF = model->one_ringF;

	for (int i = 0; i < cntVertex; i++)
	{
		//cout << "i  =    " << i << endl;
		Vertex v(i, model->_V.row(i), one_ringF);
		v.setAdjacentV(model->_F);
		//cout << v.getQ(MF) << endl;
		MV.emplace_back(v.getQ(MF)); // compute Q of each vertex and restore it to MV
		vGroup.emplace_back(v);
	}

	// add edges to  heap
	vector<V2i> E = model->_E; // the edges of the input model

	for (const V2i& e : E)
	{
		Edge edge(e.x(), e.y());
		edge.calCostAndV(MV, one_ringF, model->_V);
		//cout << "cost =  " << edge.cost << "     constraction position = " << edge.V.transpose() << endl;
		eHeap->addEdge(edge);
	}
}

void Simplification::Simplify()
{
	// the number of left faces after simplification
	int cntDelFace = static_cast<int>(1 - ratio) * cntFace; 

	for (int i = 0; i < cntDelFace; i += 2)  // 
	{//¿ªÊ¼É¾±ß	
		Edge e = eHeap->getMinEdge(); 
		Vertex v1 = vGroup[e.v1];
		v1.isDeleted = true;
		Vertex v2 = vGroup[e.v2];
		v2.isDeleted = true;

		V3d v0 = e.V;

		set<int> connectV;   // the conneected verts with Edge e
		connectV.clear();
		eHeap->delEdge(e);   //label e with deleted

		// delete e's edges
		for (const int& i: v1.adjacent_v) 
		{
			if (i != v2.id) 
			{
				eHeap->delEdge(Edge(i, v1.id));        //label Edge(i, v1.id) with deleted
				vGroup[i].adjacent_v.erase(v1.id);     // delete v1 from the connected verts' one-ring set
				connectV.insert(i);                    // add v_i to the constraction point's neighbor
			}
		}

		for (const int& i : v2.adjacent_v) {
			if (i != v2.id) {
				eHeap->delEdge(Edge(i, v2.id));        //label Edge(i, v2.id) with deleted
				vGroup[i].adjacent_v.erase(v2.id);     // delete v2 from the connected verts' one-ring set
				connectV.insert(i);                    // add v_i to the constraction point's neighbor
			}
		}

		// add new vertex to vertex group
		int newID = cntVertex++;
		Vertex v(newID, v0);
		v.adjacent_v = connectV;

		for (const int& i : connectV)
		{
			vGroup[i].adjacent_v.insert(newID);
		}

		vGroup.emplace_back(v);

		//add new vertex to e's neighbors' adjacent v
		

		//add new Edges to Heap
		for (const int& i : connectV) 
		{
			Edge e(i, newID);
			e.calCostAndV()
			eHeap->addEdge(e);
		}



	}
}

void Simplification::output()
{
}
