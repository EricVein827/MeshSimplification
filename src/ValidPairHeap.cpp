#include "ValidPairHeap.h"

ValidPair::ValidPair(const int& _u, const int& _v)
{
	id = -999;
	is_deleted = false;   // initialize the edges not to be deleted
	// we define the first vertex Id of the edge to be less then another vertex Id
	_u < _v ? v1 = _u, v2 = _v : v1 = _v, v2 = _u;
	V = V3d(0.0, 0.0, 0.0);
	cost = DINF;
}

ValidPair::~ValidPair(void)
{
}

ValidPairHeap::ValidPairHeap(const vector<PII>& edges, const vector<Eigen::Matrix4d>& M)
{
	_M = M;
	cntValidPair = 0;

	// the edges are all valid pairs , we first push edges to priority queue
	for (const PII& e: edges)
	{
		addValidPair(e.first, e.second)
		
		
	}
}



ValidPairHeap::~ValidPairHeap(void)
{
}

void ValidPairHeap::addValidPair(const int& a, const int& b, const V3d& addP)
{
	ValidPair vp(a, b);
	vp.id = cntValidPair;
	vp.V = addP;
	vp.cost = addP.transpose() * (_M[a] + _M[b]) * addP;
	pq.push(vp);

	cntValidPair++;
}


