#include "Solver.h"

Solver::Solver() : best()
{
	inst = Instance();
	dureeMax = 0;
	dureeResolution = 0;
}

Solver::Solver(Instance instance, double nbSec) : best(instance)
{
	inst = instance;
	dureeMax = nbSec;
	dureeResolution = 0;
}

Solver::Solver(double nbSec) : best()
{
	dureeMax = nbSec;
	dureeResolution = 0;
}


void Solver::setNewInstance(Instance instance)
{
	best = Result(instance);
	inst = instance;
	dureeResolution = 0;
	Reset();
}