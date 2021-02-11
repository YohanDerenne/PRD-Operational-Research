#pragma once
#include "Solver.h"
#include "SolutionPSO.h"
#include <time.h>
#include <algorithm>

class PSO :
    public Solver
{
private:
    /// <summary>
    /// Meilleur solution trouv�e
    /// </summary>
    SolutionPSO bestParticule;

    /// <summary>
    /// Nombre de particules
    /// </summary>
    int nbPart; 

    /// <summary>
    /// Particules du syst�me [0;nbPart-1]
    /// </summary>
    vector<SolutionPSO> particules;

public:
    /// <summary>
    /// Constructeur de la classe PSO
    /// </summary>
    PSO(Instance inst, double nbSec, int newNbPart);

    /// <summary>
    /// Lance la r�solution PSO
    /// </summary>
    /// <returns></returns>
    Result Solve();

    void Init();

    void CalculCrowdingDistance();

    SolutionPSO ChercherMeilleurVoisin(SolutionPSO sol);

    SolutionPSO GetRandomParticuleWithCD();
};
