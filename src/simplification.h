#pragma once
#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <time.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/adjacency_list.h>
#include <igl/per_face_normals.h>
#include "BasicDataType.h"


class Simplification
{
protected:
	MXd _V;
	MXi _F;
	MXd _N; // normals for each triangle

	// vector<vector<int>> one_ring;  // one_ring vertices  of each vertex 
	vector<vector<int>> oneRing_facet;  // one-ring triangles for each vertex

	vector< Eigen::Matrix4d> _M;  // restore every matrix for evry triangle

public:
	Simplification(const MXd& V, const MXi& F);

	~Simplification(void);

	// basic proccessing for mesh(V, F)
	void basicProccessing();

	// calcilate fundamental error quadric for every plane where the triangle lies
	void calFundamentalEQ();

	// calculate Delta for each vertex, where Delta(v) = v^T K v, as proposed in Eq.2
	Eigen::Matrix4d calVertexDelta(const int& vertexID);
	
};

#endif // !SIMPLIFICATION_H
