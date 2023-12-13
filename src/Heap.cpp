#include "Heap.h"

Heap::~Heap(void)
{
}

void Heap::addEdge(Edge& e)
{
	e.id = size;
	isDeleted.emplace_back(false);
	vert2EdgeID[make_pair(e.v1, e.v2)] = size;
	pqueue.push(e);
	size++;
}

void Heap::delEdge(const Edge& e)
{
	int i = vert2EdgeID[make_pair(e.v1, e.v2)];
	isDeleted[i] = true;
}

void Heap::delEdge(const int& a, const  int& b)
{
	int  v1 = a < b ? a : b;
	int v2 = a > b ? a : b;
	if(vert2EdgeID.count(make_pair(v1, v2)))
	{
		int i = vert2EdgeID[make_pair(v1, v2)];
		isDeleted[i] = true;
	}
}

Edge Heap::getMinEdge()
{
	if (size <= 0) {
		return Edge(0, 0);
	}

	while (isDeleted[pqueue.top().id]) {
		pqueue.pop();
	}
	Edge e = pqueue.top();
	pqueue.pop();
	return e;
}
