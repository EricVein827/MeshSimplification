#pragma once

#ifndef VALIDPAIR_H
#define	VALIDPAIR_H

#include "BasicDataType.h"


class  ValidPair
{
public:
	ValidPair(const int& _u = -99, const int& _v = -99);
	~ValidPair(void);
	int id;       //the id of the edge
	int v1, v2;   //the id of end points
	V3d V;       //the contraction target from the edge
	double cost; //the cost when the edge shrinks to a point
};

#endif // !VALIDPAIR_H

