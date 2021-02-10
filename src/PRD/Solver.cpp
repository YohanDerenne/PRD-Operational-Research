#include "Solver.h"

Solver::Solver()
{
	best = NULL;
	inst = NULL;	
}

Solver::Solver(Instance * instance, double nbSec)
{
	setNewInstance(instance);
	dureeMax = nbSec;
}

Solver::~Solver()
{
	if (best != NULL)
		delete best;
	if (inst != NULL)
		delete inst;
}

void Solver::setNewInstance(Instance* instance)
{
	if (best != NULL)
		delete best;
	if (inst != NULL)
		delete inst;
	best = NULL;
	inst = new Instance(*instance);
}
