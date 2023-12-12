#pragma once

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <igl/read_triangle_mesh.h>
#include <igl/per_face_normals.h>
#include <igl/vertex_triangle_adjacency.h>
#include "BasicDataType.h"


class BaseModel
{
public:
	MXd _V;
	MXd _N;
	MXi _F;

	vector<V2i> _E;
	vector<vector<int>> one_ringF;

	vector< Eigen::Matrix4d> _K;

	BaseModel() {};
	BaseModel(const string& modelName);
	BaseModel(const MXd& V, const MXi& F);
	~BaseModel(void);
	
	//void Eigen2Vector(const MXd& V, const MXi&F);

	void extractEdge();

	// basic proccessing for mesh(V, F)
	void basicProccessing();

	// calcilate fundamental error quadric for every plane where the triangle lies
	vector< Eigen::Matrix4d> calFundamentalEQ()const;

};

#endif // !BASEMODEL_H
