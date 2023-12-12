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

	//用于保存边，按照误差从小到大排序
	std::priority_queue<ValidPair, vector<ValidPair>, greater> pq;
	vector<Eigen::Matrix4d> _M;
	//map<PII, int> mapEdgeToID;//建立顶点到边的映射关系
	//bool isDeleted[Config::MAX_EDGE_NUM + 1];//标记哪些边被删除
	int cntValidPair;//边数量

	void addValidPair(const int& a, const int& b, const V3d& addP);//加边
	void delValidPair(ValidPair);//删边
	ValidPair getMinDelta();//删除误差最小的边
};

#endif // !VALIDPAIRHEAP_H
