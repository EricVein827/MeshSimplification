#pragma once

#ifndef HEAP_H
#define HEAP_H

#include "Edge.h"


class Heap
{
protected:
	struct greater {
		bool operator() (Edge X, Edge Y) {
			return X.cost > Y.cost;
		}
	};

public:
	std::priority_queue<Edge, vector<Edge>, greater> pqueue;
	int size;
	map<PII, int> vert2EdgeID;
	vector<bool> isDeleted;
	Heap() :size(0) {}
	~Heap(void);
	
	void addEdge(Edge& e);
	void delEdge(const Edge& e);
	void delEdge(const int& a, const  int& b);

	// return the edge whose cost is the minimum 
	Edge getMinEdge();
};

#endif // !HEAP_H
