
#include "Edge.h"

Edge::Edge(const int& u, const int& v)
{
	id = -999;
	v1 = min(u, v);
	v2 = max(u, v);
	V = V3d(0.0, 0.0, 0.0);
	cost = DINF;
	Q.setZero();
}

Edge::~Edge(void)
{
}

double Edge::quarticCost(const V3d& v) const
{
	Eigen::Vector4d newV = Eigen::Vector4d(v.x(), v.y(), v.z(), 1.0);
	return newV.transpose() * Q * newV;
}

void Edge::calCostAndV(const vector<Eigen::Matrix4d>& m, const vector<vector<int >>& one_ringF, const MXd& Verts)
{
	Vertex p1(v1, Verts.row(v1), one_ringF);
	Vertex p2(v2, Verts.row(v2), one_ringF);
	Eigen::Matrix4d Q1 = m[v1];
	Eigen::Matrix4d Q2 = m[v2];

	Q = Q1 + Q2;

	Eigen::Matrix4d T;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T(i, j) = Q(i, j);
		}
		T(3, i) = 0;
	}
	T(3, 3) = 1;

	/*cout << T << endl;
	cout << "det = " << T.determinant() << endl;*/

	if (fabs(T.determinant()) > EPS)		//det(Q) != 0
	{
		Eigen::Vector4d b(0, 0, 0, 1);
		Eigen::Vector4d X = T.inverse() * b;
	
		for (int i = 0; i < 3; i++)
			V(i) = X(i) / X(3);
		//calculate cost
		cost = quarticCost(V);
	}
	else
	{
		V3d midV = p1.position + p2.position;

		//calculate cost
		double cost1 = quarticCost(p1.position);
		double cost2 = quarticCost(p2.position);
		double cost3 = quarticCost(midV);

		double temp = cost1 < cost2 ? cost1 : cost2;
		cost = temp < cost3 ? temp : cost3;
		if (cost == cost1) V = p1.position;
		else if (cost == cost2)  V = p2.position;
		else V = midV;
	}
}

void Edge::calCostAndV(const Vertex& p1, const Vertex& p2)
{
	Eigen::Matrix4d Q1 = p1.Q;
	Eigen::Matrix4d Q2 = p2.Q;

	Q = Q1 + Q2;

	Eigen::Matrix4d T;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T(i, j) = Q(i, j);
		}
		T(3, i) = 0;
	}
	T(3, 3) = 1;

	/*cout << T << endl;
	cout << "det = " << T.determinant() << endl;*/

	if (fabs(T.determinant()) > EPS)		//det(Q) != 0
	{
		Eigen::Vector4d b(0, 0, 0, 1);
		Eigen::Vector4d X = T.inverse() * b;

		for (int i = 0; i < 3; i++)
			V(i) = X(i) / X(3);
		//calculate cost
		cost = quarticCost(V);
	}
	else
	{
		V3d midV = p1.position + p2.position;

		//calculate cost
		double cost1 = quarticCost(p1.position);
		double cost2 = quarticCost(p2.position);
		double cost3 = quarticCost(midV);

		double temp = cost1 < cost2 ? cost1 : cost2;
		cost = temp < cost3 ? temp : cost3;
		if (cost == cost1) V = p1.position;
		else if (cost == cost2)  V = p2.position;
		else V = midV;
	}
}
