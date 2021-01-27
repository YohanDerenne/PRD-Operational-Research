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
	Result * best;

	/// <summary>
	/// Donn�es contenant les param�tres du probl�me � r�soudre
	/// </summary>
	Instance * inst;

public:


	// ==================================================================

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver();

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver(Instance * instance);

	~Solver();

	/// <summary>
	/// Reset les attributs en ins�rant une nouvelle instance
	/// </summary>
	/// <param name="instance"></param>
	void setNewInstance(Instance* instance);

	/// <summary>
	/// Abstract method to solve the problem
	/// </summary>
	/// <returns></returns>
	virtual Result * Solve() = 0;
};

