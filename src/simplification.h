#pragma once

#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <time.h>
#include <omp.h>
#include <igl/writeOBJ.h>
#include "Heap.h"
#include "Face.h"


class Simplification
{
protected:
	double ratio;
	int cntFace;//the face number
	int cntVertex; // the original vertex number 

	BaseModel* model;
	Heap* eHeap;
	vector<Vertex> vGroup; // vertex gorup

	vector<Face> fGroup;  // face group

	string modelName;
public:
	Simplification(const string& _modelName);
	~Simplification(void);

	// set ratio
	void setRatio(const double& _ratio);

	//the original Heap
	void initialize();

	// simplify the mesh to a new mesh with user-defined face number
	void simplify();


	void output()const;//save the verts and faces to OBJ file.
};

#endif // !SIMPLIFICATION_H
