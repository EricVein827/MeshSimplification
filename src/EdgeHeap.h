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
	std::priority_queue<Edge, vector<Edge>, cmp> pq;//���ڱ���ߣ���������С��������
	map<PII, int> mapEdgeToID;//�������㵽�ߵ�ӳ���ϵ
	//bool isDeleted[Config::MAX_EDGE_NUM + 1];//�����Щ�߱�ɾ��
	int cntEdge;//������
	void addEdge(Edge&);//�ӱ�
	void delEdge(Edge);//ɾ��
	Edge getMinDelta();//ɾ�������С�ı�
};

#endif // !EDGEHEAP_H
