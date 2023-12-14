#pragma once

#ifndef EDGE_H
#define	EDGE_H

#include "Vertex.h"


class Edge
{
public:
	
	int id;       //the id of the edge
	int v1, v2;   //the id of end points
	V3d V;        //the shrinked point degenerated from the edge
	double cost;  //the cost when the edge shrinks to a point
	Eigen::Matrix4d Q;

	Edge(const int& _u = -99, const int& _v = -99);
	~Edge(void);

	//void calQ(const vector<Eigen::Matrix4d>& m);

	double quarticCost(const V3d& v)const;

	void calCostAndV(const vector<Eigen::Matrix4d>& m, const vector<vector<int >>& one_ringF, const MXd& Verts);

	void calCostAndV(const Vertex& v1, const Vertex& v2);
};

#endif // !EDGE_H

