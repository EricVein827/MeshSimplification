#pragma once

#ifndef EDGE_H
#define	EDGE_H

#include "Vertex.h"


class Edge : public Vertex
{
public:
	
	int id;       //the id of the edge
	int v1, v2;   //the id of end points
	V3d V;       //the shrinked point degenerated from the edge
	double cost; //the cost when the edge shrinks to a point

	Edge(const int& _u = -99, const int& _v = -99);
	~Edge(void);
	void update(const vector<Eigen::Matrix4d>& m);
	void calQ();
};

#endif // !EDGE_H

