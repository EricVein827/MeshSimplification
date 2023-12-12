
#include "Edge.h"

Edge::Edge(const int& u, const int& v)
{
	id = -999;
	v1 = min(u, v);
	v2 = max(u, v);
	V = V3d(0.0, 0.0, 0.0);
	cost = DINF;
}

Edge::~Edge(void)
{
}

void Edge::update(const vector<Eigen::Matrix4d>& m)
{
	Vertex* p1 = new Vertex(v1, _V.row(v1));
	Vertex* p2 = new Vertex(v2, _V.row(v2));
	Eigen::Matrix4d Q1 = p1->calQ(m)
	Matrix* Q2 = getQ(v2);
	Matrix* Q = add(Q1, Q2);
	double temp[4];	//save the value of Q[3]	
	for (int i = 0; i < 4; i++)
		temp[i] = Q->data[3][i];

	Q->data[3][0] = Q->data[3][1] = Q->data[3][2] = 0;
	Q->data[3][3] = 1;
	double c = 0;
	Vector_4* v;
	if (abs(det(Q)) > epsilon)		//det(Q) is not zero
	{
		Vector_4 b(0, 0, 0, 1);
		v = solve(Q, &b);
		//restore the value of Q[3]
		for (int i = 0; i < 4; i++)
			Q->data[3][i] = temp[i];
		//calculate cost
		for (int i = 0; i < 4; i++)
		{
			double cc = 0;
			for (int j = 0; j < 4; j++)
				cc += v->data[j] * Q->data[i][j];
			c += cc * v->data[i];
		}
	}
	else  //vbar = (v1+v2)/2
	{
		v = new Vector_4();
		Vector_4 vnew[3];
		for (int i = 0; i < 3; i++)
		{
			vnew[0].data[i] = (p1->coordinate[i] + p2->coordinate[i]) / 2;		//vnew[0]=(v1+v2)/2
			vnew[1].data[i] = p1->coordinate[i];		//vnew[1]=v1
			vnew[2].data[i] = p2->coordinate[i];		//vnew[2]=v2
			vnew[i].data[3] = 1;
		}
		v->data[3] = 1;
		//restore the value of Q[3]
		for (int i = 0; i < 4; i++)
			Q->data[3][i] = temp[i];
		//calculate cost
		double cost1, cost2, cost3;
		cost1 = cost2 = cost3 = 0;
		for (int i = 0; i < 4; i++)
		{
			double cc = 0;
			for (int j = 0; j < 4; j++)
				cc += vnew[0].data[j] * Q->data[i][j];
			cost1 += cc * vnew[0].data[i];
		}
		for (int i = 0; i < 4; i++)
		{
			double cc = 0;
			for (int j = 0; j < 4; j++)
				cc += vnew[1].data[j] * Q->data[i][j];
			cost2 += cc * vnew[1].data[i];
		}
		for (int i = 0; i < 4; i++)
		{
			double cc = 0;
			for (int j = 0; j < 4; j++)
				cc += vnew[2].data[j] * Q->data[i][j];
			cost3 += cc * vnew[2].data[i];
		}
		double temp = cost1 < cost2 ? cost1 : cost2;
		c = temp < cost3 ? temp : cost3;
		if (c == cost1)
		{
			for (int i = 0; i < 3; i++)
				v->data[i] = vnew[0].data[i];
		}
		else if (c == cost2)
		{
			for (int i = 0; i < 3; i++)
				v->data[i] = vnew[1].data[i];
		}
		else
		{
			for (int i = 0; i < 3; i++)
				v->data[i] = vnew[2].data[i];
		}
	}
	cost = c;

	for (int i = 0; i < 3; i++)
		vbar[i] = v->data[i];
	delete Q;
	delete Q1;
	delete Q2;
	delete v;
}
