#include "Vertex.h"

void Vertex::calQ(const vector< Eigen::Matrix4d>& m)
{
	int connectFacetN = adjacent_f.size(); // the number of adjecent triangles

	for (const int& i : adjacent_f)
	{
		Q = Q + m[i];
	}
}

void Vertex::update(const int& i, const V3d& v)
{
	id = i;
	position = v;
}

Vertex::Vertex()
{
	id = -99;
	isDeleted = false;
	position = V3d(0, 0, 0);

	adjacent_f.clear();
	adjacent_v.clear();

	Q.setZero();
}

Vertex::Vertex(const int& i, const V3d& v, const vector<vector<int>>& one_ringF)
{
	id = i;
	isDeleted = false;
	position = v;

	for (const int& af : one_ringF[id])
	{
		adjacent_f.insert(af);
	}
	adjacent_v.clear();

	Q.setZero();
}

Vertex::Vertex(const int& i, const V3d& v)
{
	id = i;
	isDeleted = false;
	position = v;

	adjacent_f.clear();
	adjacent_v.clear();

	Q.setZero();
}

void Vertex::setAdjacentV(const MXi& F)
{
	for (const int& i : adjacent_f)
	{
		V3i f = F.row(i);
		adjacent_v.insert(f.x());
		adjacent_v.insert(f.y());
		adjacent_v.insert(f.z());
	}

	adjacent_v.erase(id);
}

Vertex::~Vertex(void)
{
}

Eigen::Matrix4d Vertex::getQ(const vector< Eigen::Matrix4d>& m)
{
	calQ(m);
	return Q;
}
