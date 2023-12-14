#pragma once

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <igl/read_triangle_mesh.h>
#include <igl/per_face_normals.h>
#include <igl/vertex_triangle_adjacency.h>
#include "BasicDataType.h"


class BaseModel
{
protected:
	MXd _V;
	MXd _N;
	MXi _F;

	vector<V2i> _E;
	vector<vector<int>> one_ringF;

	vector< Eigen::Matrix4d> _K;

public:
	
	BaseModel() {};
	BaseModel(const string& modelName);
	BaseModel(const MXd& V, const MXi& F);
	~BaseModel(void);
	
	//void Eigen2Vector(const MXd& V, const MXi&F);
	void extractEdge();

	// basic proccessing for mesh(V, F)
	void basicProccessing();

	// calcilate fundamental error quadric for every plane where the triangle lies
	void calFundamentalEQ();

	// cout related information
	MXd getVert()const;
	MXd getNormal()const;
	MXi getFace()const;
	vector< Eigen::Matrix4d> getVectorMatrix()const;
	vector<vector<int>> getOneRingF()const;
	vector<V2i> getEdge()const;
};

#endif // !BASEMODEL_H
