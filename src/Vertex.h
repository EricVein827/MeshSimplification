#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "BaseModel.h"

class Vertex
{
public:
	int id;
	bool isDeleted;
	V3d position;
	set<int> adjacent_f;   // adjacent faces
	set<int> adjacent_v;   // adjacent vertices
	//set<int> planes;
	Eigen::Matrix4d Q;

	void calQ(const vector< Eigen::Matrix4d>& m);

	void update(const int& i, const V3d& v);

	Vertex();

	// turn the vertices of the model to Vertex class
	Vertex(const int& i, const V3d& v, const vector<vector<int>>& one_ringF);

	// the vert v is a contraction
	Vertex(const int& i, const V3d& v);

	void setAdjacentV(const MXi& F);

	~Vertex(void);

	Eigen::Matrix4d getQ(const vector< Eigen::Matrix4d>& m);
};


#endif // !VERTEX_H
