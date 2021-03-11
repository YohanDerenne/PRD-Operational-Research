#pragma once
#include "Solver.h"
#include "SolutionPSO.h"
#include <chrono>
#include <algorithm>
#include <random>
#include <cassert>

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

    void Init();

    void CalculCrowdingDistance();
    

public:

    /// <summary>
    /// Particules du système [0;nbPart-1]
    /// </summary>
    vector<SolutionPSO> particules;

    /// <summary>
    /// Constructeur de la classe PSO
    /// </summary>
    PSO(Instance inst, double nbSec, int newNbPart);

    /// <summary>
    /// Lance la résolution PSO
    /// </summary>
    /// <returns></returns>
    Result Solve();



    SolutionPSO ChercherMeilleurVoisin(SolutionPSO sol);
    SolutionPSO VoisinSwitchsv1sv2(SolutionPSO sol);
    SolutionPSO VoisinSv1Bloc(SolutionPSO sol);
    SolutionPSO VoisinAleaIdle(SolutionPSO sol);
    SolutionPSO VoisinIdleNext(SolutionPSO sol);
    SolutionPSO VoisinMelangeSv2(SolutionPSO sol);

    SolutionPSO GetRandomParticuleWithCD();

    Result GetReference();
    
    bool StopCondition();
};

