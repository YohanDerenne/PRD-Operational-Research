#include "SolverControler.h"

SolverControler::SolverControler()
{
    solver = NULL;
    results = list<Result>();
    instances = list<Instance>();
}

SolverControler::~SolverControler()
{
    if (solver != NULL)
        delete solver;
}

void SolverControler::LaunchComputation()
{
    
}

bool SolverControler::ImportInstances(string dir)
{
    return false;
}

bool SolverControler::ExportResults(string path)
{
    return false;
}
