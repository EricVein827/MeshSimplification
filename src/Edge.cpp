#include "Edge.h"

Edge::Edge(const int& _u, const int& _v)
{
	id = -999;
	v1 = _u;
	v2 = _v;
	V = V3d(0.0, 0.0, 0.0);
	cost = DINF * 1.0;
}

Edge::~Edge(void)
{
}
