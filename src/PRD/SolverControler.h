#pragma once
#include "Solver.h"
#include <map>


class SolverControler
{
private:
	Solver* solver;
	map<Instance, Result> data;

public:
	SolverControler();
	void LaunchComputation();
	bool ImportInstances(string dir);
	bool ExportResults(string path);
};

