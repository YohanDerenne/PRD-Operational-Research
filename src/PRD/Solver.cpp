#include "Solver.h"

Solver::Solver()
{
	best = NULL;
	inst = NULL;	
}

Solver::Solver(Instance * instance)
{
	setNewInstance(instance);
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
	delete best;
	delete inst;
	best = new Result(instance);
	inst = new Instance(*instance);
}
