#pragma once
#include "Solver.h"
class TabouSearch :
    protected Solver
{
public:
    /// <summary>
    /// Constructeur de la classe de r�solution Tabou
    /// </summary>
    TabouSearch();

    /// <summary>
    /// Lance la r�solution
    /// </summary>
    /// <returns></returns>
    Result * Solve();
};

