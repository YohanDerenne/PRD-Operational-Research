#include "SolverControler.h"

SolverControler::SolverControler()
{
    solver = NULL;
    data = map<Instance, Result>();
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
