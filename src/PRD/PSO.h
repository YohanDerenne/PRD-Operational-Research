#pragma once
#include "Solver.h"
#include "SolutionPSO.h"
#include <chrono>
#include <algorithm>
#include <random>
#include <cassert>

/// <summary>
/// Compare deux solutions en fonction de leur résultats (cout_total)
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
bool comparator(SolutionPSO i, SolutionPSO j);

/// <summary>
/// Géere un double entre deux bornes
/// </summary>
/// <param name="inf">Borne inférieur</param>
/// <param name="sup">Borne Supérieur</param>
/// <returns></returns>
double generateDouble(double inf, double sup);

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
    /// Initialise la PSO
    /// </summary>
    void Init();

    /// <summary>
    /// Initialise les références et les insére en tant que première particules
    /// </summary>
    void InitReferences();

    /// <summary>
    /// Solution de référence afin de comparer les résultats trouvés
    /// </summary>
    Result reference;

    /// <summary>
    /// Calcul les crowding distances de chaque particules
    /// </summary>
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
    /// Constructeur de la classe PSO
    /// </summary>
    PSO(double nbSec, int newNbPart);

    /// <summary>
    /// Lance la résolution PSO
    /// </summary>
    /// <returns>Resultat de la solution trouvée</returns>
    Result Solve();

    /// <summary>
    /// Reset les attributs de la PSO
    /// </summary>
    void Reset();

    /****************************** VOISIN ******************************/

    /// <summary>
    /// Rercherche le meilleur voisin
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO ChercherMeilleurVoisin(SolutionPSO sol);

    /// <summary>
    /// Rercherche un meilleur voisin en réalisant des permutation sur les vecteurs sv1 et v2
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO VoisinSwitchsv1sv2(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en réalisant des permutation par bloc sur le vecteur sv1
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO VoisinSv1Bloc(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en modifiant aléatoirement le vecteur sv3
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO VoisinAleaIdle(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en modifiant le vecteur sv3 en fonction du cout d'inventaire
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO VoisinIdleNext(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en mélangeant les données du vecteur sv2
    /// </summary>
    /// <param name="sol">Solution où on cherche les voisins</param>
    /// <returns>Meilleur voisin trouvé, sinon retourne la solution qui était en parametre</returns>
    SolutionPSO VoisinMelangeSv2(SolutionPSO sol);

    /****************************** END VOISIN ******************************/

    /// <summary>
    /// Recupere une particule aléatoire en fonction de son coef CD
    /// </summary>
    /// <returns>Particule aléatoire</returns>
    SolutionPSO GetRandomParticuleWithCD();

    /// <summary>
    /// Recupére une solution de référence pour comparer les résultats
    /// </summary>
    /// <returns>Solution de référence</returns>
    Result GetReference();
    
    /// <summary>
    /// Condition d'arret de l'algorithme PSO
    /// </summary>
    /// <returns>1 pour arret, 0 sinon</returns>
    bool StopCondition();
};

