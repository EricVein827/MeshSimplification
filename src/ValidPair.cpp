#include "ValidPair.h"


ValidPair::ValidPair(const int& _u, const int& _v)
{
	id = -999;

	// we define the first vertex Id of the edge to be less then another vertex Id
	_u < _v ? v1 = _u, v2 = _v : v1 = _v, v2 = _u;
	V = V3d(0.0, 0.0, 0.0);
	cost = DINF;
}

ValidPair::~ValidPair(void)
{
}

