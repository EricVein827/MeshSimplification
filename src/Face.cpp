#include "Face.h"

Face::Face(const int& a, const int& b, const int& c)
{
	F = V3i(a, b, c);

	isDeleted = false;

	Q.setZero();
}

void Face::calQ(const vector< Vertex>& vGroup)
{
	V3d v0 = vGroup[F.x()].position;
	V3d v1 = vGroup[F.y()].position;
	V3d v2 = vGroup[F.z()].position;

	N = (v1 - v0).cross(v2 - v0).normalized();

	Eigen::Vector4d temp(N.x(), N.y(), N.z(), -v0.dot(N));

	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			Q(j, k) += temp(k) * temp(j);
		}
	}
}
