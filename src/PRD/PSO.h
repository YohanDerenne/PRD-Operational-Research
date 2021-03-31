#pragma once
#include "Solver.h"
#include "SolutionPSO.h"
#include <chrono>
#include <algorithm>
#include <random>
#include <cassert>

/// <summary>
/// Compare deux solutions en fonction de leur r�sultats (cout_total)
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
bool comparator(SolutionPSO i, SolutionPSO j);

/// <summary>
/// G�ere un double entre deux bornes
/// </summary>
/// <param name="inf">Borne inf�rieur</param>
/// <param name="sup">Borne Sup�rieur</param>
/// <returns></returns>
double generateDouble(double inf, double sup);

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
    /// Initialise la PSO
    /// </summary>
    void Init();

    /// <summary>
    /// Initialise les r�f�rences et les ins�re en tant que premi�re particules
    /// </summary>
    void InitReferences();

    /// <summary>
    /// Solution de r�f�rence afin de comparer les r�sultats trouv�s
    /// </summary>
    Result reference;

    /// <summary>
    /// Calcul les crowding distances de chaque particules
    /// </summary>
    void CalculCrowdingDistance();
    

public:

    /// <summary>
    /// Particules du syst�me [0;nbPart-1]
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
    /// Lance la r�solution PSO
    /// </summary>
    /// <returns>Resultat de la solution trouv�e</returns>
    Result Solve();

    /// <summary>
    /// Reset les attributs de la PSO
    /// </summary>
    void Reset();

    /****************************** VOISIN ******************************/

    /// <summary>
    /// Rercherche le meilleur voisin
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO ChercherMeilleurVoisin(SolutionPSO sol);

    /// <summary>
    /// Rercherche un meilleur voisin en r�alisant des permutation sur les vecteurs sv1 et v2
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO VoisinSwitchsv1sv2(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en r�alisant des permutation par bloc sur le vecteur sv1
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO VoisinSv1Bloc(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en modifiant al�atoirement le vecteur sv3
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO VoisinAleaIdle(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en modifiant le vecteur sv3 en fonction du cout d'inventaire
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO VoisinIdleNext(SolutionPSO sol);

    /// <summary>
    /// Recherche le meilleur voisin en m�langeant les donn�es du vecteur sv2
    /// </summary>
    /// <param name="sol">Solution o� on cherche les voisins</param>
    /// <returns>Meilleur voisin trouv�, sinon retourne la solution qui �tait en parametre</returns>
    SolutionPSO VoisinMelangeSv2(SolutionPSO sol);

    /****************************** END VOISIN ******************************/

    /// <summary>
    /// Recupere une particule al�atoire en fonction de son coef CD
    /// </summary>
    /// <returns>Particule al�atoire</returns>
    SolutionPSO GetRandomParticuleWithCD();

    /// <summary>
    /// Recup�re une solution de r�f�rence pour comparer les r�sultats
    /// </summary>
    /// <returns>Solution de r�f�rence</returns>
    Result GetReference();
    
    /// <summary>
    /// Condition d'arret de l'algorithme PSO
    /// </summary>
    /// <returns>1 pour arret, 0 sinon</returns>
    bool StopCondition();
};

