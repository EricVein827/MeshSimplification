#pragma once

#ifndef EDGE_H
#define	EDGE_H

#include "BasicDataType.h"

// edge class, used for 
class Edge
{
public:
	Edge(const int& _u = -99, const int& _v = -99);
	~Edge(void);
	int id;       //the id of the edge
	int v1, v2;   //the id of end points
	V3d V;       //the shrinked point degenerated from the edge
	double cost; //the cost when the edge shrinks to a point
};

#endif // !EDGE_H

