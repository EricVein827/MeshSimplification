#include "simplification.h"

Simplification::Simplification(const MXd& V, const MXi& F)
{
	_V = V;
	_F = F;
	
	basicProccessing();
}

Simplification::~Simplification(void)
{
}

void Simplification::basicProccessing()
{
	// calculate normals of each triangle
	igl::per_face_normals(_V, _F, _N);
	//cout << _N.rowwise().norm() << endl;

	// igl::adjacency_list(_F, one_ring);   // get one-ring vertex id for each vertex

	vector<vector<int>>  Fi;
	igl::vertex_triangle_adjacency(_V, _F, oneRing_facet, Fi);
}

void Simplification::calFundamentalEQ()
{
	Eigen::Matrix4d K;   // fundamental error quadrics matrix 
	for (int i = 0; i < _F.rows(); i++)
	{
		K.setZero();

		V3d unitNormal = _N.row(i);   // get the unti nornal of each adjacent triangle
		V3i f = _F.row(i);
		V3d v = _V.row(f.x());

		Eigen::Vector4d p(unitNormal.x(), unitNormal.y(), unitNormal.z(), -v.dot(unitNormal)); // fundamental error quadric

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				K(j, k) += p(k) * p(j);
			}
		}

		_M.emplace_back(K);
	}
}

Eigen::Matrix4d Simplification::calVertexDelta(const int& vertexID)
{
	Eigen::Matrix4d Delta;   // equivalent to Q proposed in the paper QEM Simplification
	Delta.setZero();

	int connectFacetN = oneRing_facet[vertexID].size(); // the number of adjecent triangles

	for (int i = 1; i < connectFacetN; i++)
	{
		int adjacentF = oneRing_facet[vertexID][i];

		Delta = Delta + _M[adjacentF];
	}

	return Delta;
}
