#include "SolverControler.h"

SolverControler::SolverControler()
{
    solver = NULL;
    results = list<Result>();
    instances = list<Instance>();
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
