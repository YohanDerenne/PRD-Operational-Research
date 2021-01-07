#pragma once
#include "Solver.h"
class TabouSearch :
    protected Solver
{
public:
    /// <summary>
    /// Constructeur de la classe de résolution Tabou
    /// </summary>
    TabouSearch();

    /// <summary>
    /// Lance la résolution
    /// </summary>
    /// <returns></returns>
    Result * Solve();
};

