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

	~Solver();

	/// <summary>
	/// Reset les attributs en ins�rant une nouvelle instance
	/// </summary>
	/// <param name="instance"></param>
	void setNewInstance(Instance instance);

	/// <summary>
	/// Abstract method to solve the problem
	/// </summary>
	/// <returns></returns>
	virtual Result Solve() = 0;

	double getDureeResolution() { return dureeResolution; }
};

