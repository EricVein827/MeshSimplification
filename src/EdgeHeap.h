#pragma once
#ifndef EDGEHEAP_H
#define EDGEHEAP_H
#include "Edge.h"

class EdgeHeap
{
public:
	EdgeHeap(void);
	~EdgeHeap(void);
	struct cmp {
		bool operator() (Edge X, Edge Y) {
			return X.cost > Y.cost;
		}
	};
	std::priority_queue<Edge, vector<Edge>, cmp> pq;//用于保存边，按照误差从小到大排序
	map<PII, int> mapEdgeToID;//建立顶点到边的映射关系
	//bool isDeleted[Config::MAX_EDGE_NUM + 1];//标记哪些边被删除
	int cntEdge;//边数量
	void addEdge(Edge&);//加边
	void delEdge(Edge);//删边
	Edge getMinDelta();//删除误差最小的边
};

#endif // !EDGEHEAP_H
