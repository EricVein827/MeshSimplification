#include "simplification.h"

Simplification::Simplification(const MXd& V, const MXi& F)
{
	_V = V;
	_F = F;
	
	basicProccessing();

	vector< Eigen::Matrix4d> MF = calFundamentalEQ();
	for (int i = 0; i < _V.rows(); i++)
	{
		Eigen::Matrix4d matrixV = calVertexDelta(i, MF);
		_MV.emplace_back(matrixV);
	}
	MF.clear();

}

Simplification::~Simplification(void)
{
}

void Simplification::extractEdge()
{
	set<PII> uset;

	for (int i = 0; i < _F.rows(); i++)
	{
		V3i f = _F.row(i);
		int maxF = f.maxCoeff();
		int minF = f.minCoeff();
		int middleF = f.sum() - maxF - minF;

		uset.insert(make_pair(minF, middleF));
		uset.insert(make_pair(middleF, maxF));
		uset.insert(make_pair(minF, maxF));
	}

	for (const PII& it : uset)
		_E.emplace_back(V2i(it.first, it.second));
}

void Simplification::basicProccessing()
{
	// calculate normals of each triangle
	igl::per_face_normals(_V, _F, _N);
	//cout << _N.rowwise().norm() << endl;

	extractEdge();

	// igl::adjacency_list(_F, one_ring);   // get one-ring vertex id for each vertex
	vector<vector<int>>  Fi;
	igl::vertex_triangle_adjacency(_V, _F, oneRing_facet, Fi);
}

vector< Eigen::Matrix4d> Simplification::calFundamentalEQ()
{
	vector< Eigen::Matrix4d> MF;  // restore matrix for every triangle
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

		MF.emplace_back(K);
	}

	return MF;
}

Eigen::Matrix4d Simplification::calVertexDelta(const int& vertexID, const vector< Eigen::Matrix4d>& MF)
{
	Eigen::Matrix4d Delta;   // equivalent to Q proposed in the paper QEM Simplification
	Delta.setZero();

	int connectFacetN = oneRing_facet[vertexID].size(); // the number of adjecent triangles

	for (int i = 0; i < connectFacetN; i++)
	{
		int adjacentF = oneRing_facet[vertexID][i];

		Delta = Delta + MF[adjacentF];
	}

	return Delta;
}

V3d Simplification::calContractionPosition(const ValidPair& vp, Eigen::Matrix4d matrix)
{
	matrix(3, 0) = 0.0;
	matrix(3, 1) = 0.0;
	matrix(3, 2) = 0.0;
	matrix(3, 3) = 1.0;

	if (fabs(matrix.determinant()) <= EPS)
	{
		return 0.5 * (_V.row(vp.v1) + _V.row(vp.v2));
	}
	
	Eigen::Vector4d b(0, 0, 0, 1);
	Eigen::Vector4d X = matrix.inverse() * b;
	
	V3d newPoint = V3d(X(0), X(1), X(2)) / X(3);
	return newPoint;
}
