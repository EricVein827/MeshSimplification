#pragma once

#ifndef FACE_H
#define FACE_H
#include "Vertex.h"


class Face
{
public:
	V3i F;
	V3d N;
	Eigen::Matrix4d Q;

	bool isDeleted;
public:
	Face(const V3i& _F, const V3d& _N, const Eigen::Matrix4d& _Q) :F(_F), N(_N), Q(_Q), isDeleted(false){};
	
	Face(const int& a, const int& b, const int& c);

	~Face(void) {};

	void calQ(const vector< Vertex>& vGroup);
	
};

#endif // !FACE_H



