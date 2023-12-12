#include <igl/read_triangle_mesh.h>
#include <time.h>

#include "BaseModel.h"


int main(int argc, char* argv[])
{
	/*MXd vertices;
	MXi faces;
	igl::read_triangle_mesh(argv[1], vertices, faces);*/
	
	// TEST
	const string fileName = "..//models//Buddha.obj";
	BaseModel model(fileName);

	vector< Eigen::Matrix4d> MF = model.calFundamentalEQ();
	

	return 0;
}