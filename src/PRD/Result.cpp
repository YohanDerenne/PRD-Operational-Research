#include "Result.h"

Result::Result(Instance* instance)
{
	inst = new Instance(*instance);

	y = vector<vector<bool>>();
	Z = vector<bool>();
	z = vector<vector<bool>>();
	x = vector<vector<vector<bool>>>();
	D_M = vector<int>();
	C = vector<vector<int>>();
	F = vector<int>();
	f = vector<int>();
	PT_M = vector<unsigned int>();
	IC_WIP = 0;
	IC_FIN = 0;
	IC = 0;
	PPC_M = 0;

	D_3PL = vector<int>();
	T_M = vector<int>();
	VC = 0;
}

Result::Result(const Result& res2)
{
	inst = new Instance(*res2.inst);

	y = res2.y;
	Z = res2.Z;
	z = res2.z;
	x = res2.x;
	D_M = res2.D_M;
	C = res2.C;
	F = res2.F;
	f = res2.f;
	PT_M = res2.PT_M;
	IC_WIP = res2.IC_WIP;
	IC_FIN = res2.IC_FIN;
	IC = res2.IC;
	PPC_M = res2.PPC_M;

	D_3PL = res2.D_3PL;
	T_M = res2.T_M;
	VC = res2.VC;

	cout_total = res2.cout_total;
}

Result::~Result()
{
	if (inst != NULL) {
		delete inst;
	}
}
