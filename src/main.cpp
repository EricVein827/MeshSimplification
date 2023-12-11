#include <igl/read_triangle_mesh.h>

#include "simplification.h"


int main(int argc, char* argv[])
{
	/*MXd vertices;
	MXi faces;
	igl::read_triangle_mesh(argv[1], vertices, faces);*/
	
	// TEST
	const string fileName = "..//models//Buddha.obj";
	MXd vertices;
	MXi faces;
	igl::read_triangle_mesh(fileName, vertices, faces);

	Simplification s(vertices, faces);
	//vector<vector<int>> VF;
	//vector<vector<int>> VFi;
	//igl::vertex_triangle_adjacency(vertices, faces, VF, VFi);

	int a = 0;
	return 0;
}