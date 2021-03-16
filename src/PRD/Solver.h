#pragma once
#include "Result.h"
#include <vector> 
#include <string>

using namespace std;

class Solver
{
protected:
	/// <summary>
	/// Données contenant les résultats après la résolution
	/// </summary>
	Result best;

	/// <summary>
	/// Données contenant les paramètres du problème à résoudre
	/// </summary>
	Instance inst;


	/// <summary>
	/// Condiation d'arrêt de la PSO. Durée maximum de traitement en secondes
	/// </summary>
	double dureeMax;

	/// <summary>
	/// Durée utilisée pour trouver la solution
	/// </summary>
	double dureeResolution;

public:


	// ==================================================================

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver();

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver(Instance instance, double nbSec);


	/// <summary>
	/// Reset les attributs en insérant une nouvelle instance
	/// </summary>
	/// <param name="instance">Nouvelle instance sur laquelle le solver doit travailler</param>
	void setNewInstance(Instance instance);

	/// <summary>
	/// Abstract method to solve the problem
	/// </summary>
	/// <returns>Le résultat trouvé par l'algorithme</returns>
	virtual Result Solve() = 0;

	/// <summary>
	/// Recupere le temps utilisée pour trouver la solution
	/// </summary>
	/// <returns>La durée pour trouver la solution</returns>
	double getDureeResolution() { return dureeResolution; }
};

