#include "Vertex.h"

void Vertex::calQ(const vector< Eigen::Matrix4d>& m)
{
	Q.setZero();

	int connectFacetN = adjacent_v.size(); // the number of adjecent triangles

	for (const int& i : adjacent_v)
	{
		Q = Q + m[i];
	}
}

void Vertex::update(const int i, const V3d& v)
{
	id = i;
	position = v;
}

Vertex::Vertex()
{
	id = -99;
	valid = true;
	position = V3d(0, 0, 0);

	for (const int& af : one_ringF[i])
	{
		adjacent_v.insert(af);
	}
}

Vertex::Vertex(const int i, const V3d& v)
{
	id = i;
	valid = true;
	position = v;

	for (const int& af : one_ringF[i])
	{
		adjacent_v.insert(af);
	}
}

Vertex::~Vertex(void)
{
}
