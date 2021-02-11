#include "Solver.h"

Solver::Solver() : best(Instance())
{
	inst = Instance();
	dureeMax = 0;
}

Solver::Solver(Instance instance, double nbSec) : best(instance)
{
	inst = instance;
	dureeMax = nbSec;
}

Solver::~Solver()
{
}

void Solver::setNewInstance(Instance instance)
{
	best = Result(instance);
	inst = instance;
}
