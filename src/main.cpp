#include "Simplification.h"


int main(int argc, char* argv[])
{
	/*MXd vertices;
	MXi faces;
	igl::read_triangle_mesh(argv[1], vertices, faces);*/
	
	// ************************************  basic *******************************************
	const string fileName = "..//models//Buddha.obj";
	Simplification* meshSimplify = new Simplification(fileName);
	meshSimplify->setRatio(2);

	meshSimplify->initialize();

//	BaseModel model(fileName);
//
//	MXd V = model._V;
//	MXi F = model._F;
//	vector<V2i> E = model._E; // the edges of the input model
//
//	vector<Eigen::Matrix4d> MF = model._K;
//
//	vector<vector<int >> one_ringF = model.one_ringF;
//
//	// *****************************************  vert *********************************************
//	vector< Eigen::Matrix4d> MV;   // vertex group
//	//cout << "number of available processors: " << omp_get_num_procs() << endl;
//	clock_t start = clock();
//
////#pragma omp parallel for
//	for (int i = 0; i < V.rows(); i++)
//	{
//		//cout << "i  =    " << i << endl;
//		Vertex v(i, V.row(i), one_ringF);
//		//cout << v.getQ(MF) << endl;
//		MV.emplace_back(v.getQ(MF));
//	}
//	clock_t end = clock();
//	cout << " time used: " << end - start << endl;
//
//	// ***********************************************  heap ***********************************************
//	Heap hE;
//
//	start = clock();
//	for (const V2i& e : E)
//	{
//		Edge edge(e.x(), e.y());
//		edge.calCostAndV(MV, one_ringF, V);
//		//cout << "cost =  " << edge.cost << "     constraction position = " << edge.V.transpose() << endl;
//		hE.addEdge(edge);
//	}
//	end = clock();
//	cout << " establishing heap cost time : " << end - start << endl;
//
//	// ******************************** simplification **********************************************************
//	Edge minE = hE.getMinEdge();  // the edge equipped with minimum cost  
//	V3d addV = minE.V;
//	Vertex newV = Vertex();


	return 0;
}