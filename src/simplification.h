#pragma once

#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <time.h>
#include <omp.h>
#include "Heap.h"


class FaceGroup
{
public:
	FaceGroup(const V3i& _F, const V3d& _N) :F(_F), N(_N) {};
	~FaceGroup(void) {};
	V3i F;
	V3d N;
};

class Simplification
{
protected:
	double ratio;
	int cntFace;//the face number
	int cntVertex; // the original vertex number 

	BaseModel* model;
	Heap* eHeap;
	vector<Vertex> vGroup; // vertex gorup

	vector<FaceGroup> fGroup;  // face group
public:
	Simplification(const string& modelName);
	~Simplification(void);

	// set ratio
	void setRatio(const double& _ratio);

	//the original Heap
	void initialize();

	// simplify the mesh to a new mesh with user-defined face number
	void Simplify();


	void output();//Êä³ö½á¹û
};

#endif // !SIMPLIFICATION_H
