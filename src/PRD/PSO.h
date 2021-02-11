#pragma once
#include "Solver.h"
#include "SolutionPSO.h"
class PSO :
    public Solver
{
private:
    /// <summary>
    /// Meilleur solution trouvée
    /// </summary>
    SolutionPSO bestParticule;

    /// <summary>
    /// Nombre de particules
    /// </summary>
    int nbPart; 

    /// <summary>
    /// Particules du système [0;nbPart-1]
    /// </summary>
    vector<SolutionPSO> particules;

public:
    /// <summary>
    /// Constructeur de la classe PSO
    /// </summary>
    PSO(Instance inst, double nbSec, int newNbPart);

    /// <summary>
    /// Lance la résolution PSO
    /// </summary>
    /// <returns></returns>
    Result Solve();

    void Init();

    void CalculCrowdingDistance();

    SolutionPSO ChercherMeilleurVoisin(SolutionPSO sol);
};

