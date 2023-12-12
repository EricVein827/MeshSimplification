#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "BaseModel.h"

class Vertex : public BaseModel
{
public:
	int id;
	bool valid;
	V3d position;
	set<int> adjacent_v;
	set<int> planes;
	Eigen::Matrix4d Q;

	void calQ(const vector< Eigen::Matrix4d>& m);

	void update(const int i, const V3d& v);

	Vertex();

	Vertex(const int i, const V3d& v);

	~Vertex(void);
};


#endif // !VERTEX_H
