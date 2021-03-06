#pragma once
#include "Solution.h"
class SolutionPSO :
    public Solution
{
public :
    /// <summary>
    /// Velocit� pour le vecteur sv1
    /// </summary>
    vector<double> velSv1;

    /// <summary>
    /// Velocit� pour le vecteur sv2
    /// </summary>
    vector<double> velSv2;

    /// <summary>
    /// V�locit� pour le vecteur sv3
    /// </summary>
    vector<vector<double>> velSv3;

    /// <summary>
    /// Coefficient de la Crowding Distance
    /// </summary>
    double CDcoef;

    /// <summary>
    /// Constructeur avec pour parametre une instance
    /// </summary>
    /// <param name="inst">Instance sur laquelle la solution se base</param>
    SolutionPSO(Instance inst);
};

