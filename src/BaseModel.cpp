
#include "BaseModel.h"

BaseModel::BaseModel(const string& modelName)
{
	igl::read_triangle_mesh(modelName, _V, _F);
	
	basicProccessing();

	_K = calFundamentalEQ();
}

BaseModel::BaseModel(const MXd& V, const MXi& F)
{
	_V = V;
	_F = F;

	basicProccessing();

	_K = calFundamentalEQ();
}

BaseModel::~BaseModel(void)
{
}

//
//void BaseModel::Eigen2Vector(const MXd& V, const MXi& F)
//{
//	for (int i = 0; i < V.rows(); i++)
//	{
//		_V.emplace_back(V.row(i));
//	}
//	for (int i = 0; i < F.rows(); i++)
//	{
//		_F.emplace_back(F.row(i));
//	}
//}

void BaseModel::extractEdge()
{
	set<PII> uset;

	for (int i = 0; i < _F.rows(); i++)
	{
		const V3i f = _F.row(i);
		int maxF = f.maxCoeff();
		int minF = f.minCoeff();
		int middleF = f.sum() - maxF - minF;

		uset.insert(make_pair(minF, middleF));
		uset.insert(make_pair(middleF, maxF));
		uset.insert(make_pair(minF, maxF));
	}

	for (const PII& it : uset)
		_E.emplace_back(V2i(it.first, it.second));
}

void BaseModel::basicProccessing()
{
	// calculate normals of each triangle
	igl::per_face_normals(_V, _F, _N);
	//cout << _N.rowwise().norm() << endl;

	extractEdge();

	// igl::adjacency_list(_F, one_ring);   // get one-ring vertex id for each vertex
	vector<vector<int>>  Fi;
	igl::vertex_triangle_adjacency(_V, _F, one_ringF, Fi);
}

vector<Eigen::Matrix4d> BaseModel::calFundamentalEQ()const
{
	vector< Eigen::Matrix4d> MF;  // restore matrix for every triangle
	Eigen::Matrix4d K;   // fundamental error quadrics matrix 
	for (int i = 0; i < _F.rows(); i++)
	{
		K.setZero();

		V3d unitNormal = _N.row(i);   // get the unti nornal of each adjacent triangle
		V3i f = _F.row(i);
		V3d v = _V.row(f.x());

		Eigen::Vector4d p(unitNormal.x(), unitNormal.y(), unitNormal.z(), -v.dot(unitNormal)); // fundamental error quadric

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				K(j, k) += p(k) * p(j);
			}
		}

		MF.emplace_back(K);
	}

	return MF;
}
