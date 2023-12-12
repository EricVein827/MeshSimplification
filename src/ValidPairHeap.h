#pragma once

#ifndef VALIDPAIRHEAP_H
#define VALIDPAIRHEAP_H

#include "BasicDataType.h"


class  ValidPair
{
public:
	ValidPair(const int& _u = -99, const int& _v = -99);
	~ValidPair(void);
	int id;       //the id of the edge
	int v1, v2;   //the id of end points
	bool is_deleted;   // whether the edge is deleted
	V3d V;       //the contraction target from the edge
	double cost; //the cost when the edge shrinks to a point
};


class ValidPairHeap
{
public:
	ValidPairHeap(const vector<PII>& edges, const vector<Eigen::Matrix4d>& M);
	~ValidPairHeap(void);

	struct greater {
		bool operator() (ValidPair X, ValidPair Y) {
			return X.cost > Y.cost;
		}
	};

	//���ڱ���ߣ���������С��������
	std::priority_queue<ValidPair, vector<ValidPair>, greater> pq;
	vector<Eigen::Matrix4d> _M;
	//map<PII, int> mapEdgeToID;//�������㵽�ߵ�ӳ���ϵ
	//bool isDeleted[Config::MAX_EDGE_NUM + 1];//�����Щ�߱�ɾ��
	int cntValidPair;//������

	void addValidPair(const int& a, const int& b, const V3d& addP);//�ӱ�
	void delValidPair(ValidPair);//ɾ��
	ValidPair getMinDelta();//ɾ�������С�ı�
};

#endif // !VALIDPAIRHEAP_H
