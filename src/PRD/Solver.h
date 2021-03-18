#pragma once
#include "Result.h"
#include <vector> 
#include <string>

using namespace std;

class Solver
{
protected:
	/// <summary>
	/// Donn�es contenant les r�sultats apr�s la r�solution
	/// </summary>
	Result best;

	/// <summary>
	/// Donn�es contenant les param�tres du probl�me � r�soudre
	/// </summary>
	Instance inst;


	/// <summary>
	/// Condiation d'arr�t de la PSO. Dur�e maximum de traitement en secondes
	/// </summary>
	double dureeMax;

	/// <summary>
	/// Dur�e utilis�e pour trouver la solution
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
	/// <param name="instance">Instance de la r�soltion</param>
	/// <param name="nbSec">Duree max de la r�solution</param>
	Solver(Instance instance, double nbSec);

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	/// <param name="nbSec">Duree max de la r�solution</param>
	Solver(double nbSec);


	/// <summary>
	/// Reset les attributs en ins�rant une nouvelle instance
	/// </summary>
	/// <param name="instance">Nouvelle instance sur laquelle le solver doit travailler</param>
	void setNewInstance(Instance instance);

	/// <summary>
	/// Abstract method to solve the problem
	/// </summary>
	/// <returns>Le r�sultat trouv� par l'algorithme</returns>
	virtual Result Solve() = 0;

	/// <summary>
	/// Reset les attributs du solver
	/// </summary>
	virtual void Reset() = 0;

	/// <summary>
	/// Recupere le temps utilis�e pour trouver la solution
	/// </summary>
	/// <returns>La dur�e pour trouver la solution</returns>
	double getDureeResolution() { return dureeResolution; }
};

