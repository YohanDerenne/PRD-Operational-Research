#include "Solver.h"

Solver::Solver()
{
	res = NULL;
	inst = NULL;

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

Solver::Solver(Instance * instance)
{
	setNewInstance(instance);
}

Solver::~Solver()
{
	if (res != NULL)
		delete res;
	if (inst != NULL)
		delete inst;
}

void Solver::setNewInstance(Instance* instance)
{
	res = new Result(instance);
	inst = instance;

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
