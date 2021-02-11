#pragma once
#include "Solution.h"
class SolutionPSO :
    public Solution
{
public :
    /// <summary>
    /// Velocité pour le vecteur sv1
    /// </summary>
    vector<double> velSv1;

    /// <summary>
    /// Velocité pour le vecteur sv2
    /// </summary>
    vector<double> velSv2;

    /// <summary>
    /// Vélocité pour le vecteur sv3
    /// </summary>
    vector<vector<double>> velSv3;

    /// <summary>
    /// Coefficient de la Crowding Distance
    /// </summary>
    double CDcoef;

    SolutionPSO(Instance inst);
};

