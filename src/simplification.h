#pragma once
#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <igl/vertex_triangle_adjacency.h>
#include <igl/adjacency_list.h>
#include <igl/per_face_normals.h>

#include "BasicDataType.h"
#include "ValidPairHeap.h"


class Simplification
{
protected:
	MXd _V;
	MXi _F;
	MXd _N; // normals for each triangle
	vector<V2i> _E; // edges

	// vector<vector<int>> one_ring;  // one_ring vertices  of each vertex 
	vector<vector<int>> oneRing_facet;  // one-ring triangles for each vertex

	vector< Eigen::Matrix4d> _MV;  // restore matrix for every vertices

public:
	Simplification(const MXd& V, const MXi& F);

	~Simplification(void);

	void extractEdge();

	// basic proccessing for mesh(V, F)
	void basicProccessing();

	// calcilate fundamental error quadric for every plane where the triangle lies
	vector< Eigen::Matrix4d> calFundamentalEQ();

	// calculate Delta for each vertex, where Delta(v) = v^T K v, as proposed in Eq.2
	Eigen::Matrix4d calVertexDelta(const int& vertexID, const vector< Eigen::Matrix4d>& MF);
	
	V3d calContractionPosition(const ValidPair& vp, Eigen::Matrix4d matrix);
};

#endif // !SIMPLIFICATION_H
