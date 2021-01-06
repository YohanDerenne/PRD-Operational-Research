#pragma once
#include "Result.h"
#include <vector> 
#include <string>

using namespace std;

class Solver
{
public:
	Result * res;
	Instance * inst;

	vector<vector<bool>> y;
	vector<bool> Z;
	vector<vector<bool>> z;
	vector<vector<vector<bool>>> x;
	vector<int> D_M;
	vector<vector<int>> C;
	vector<int> F;
	vector<int> f;
	vector<int> PT_M;
	double IC_WIP;
	double IC_FIN;
	double IC;
	double PPC_M;

	vector<int> D_3PL;
	vector<int> T_M;
	double VC;

	Solver(Instance * instance);

};

