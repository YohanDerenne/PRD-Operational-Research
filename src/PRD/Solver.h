#pragma once
#include "Result.h"
#include <vector> 
#include <string>

using namespace std;

class Solver
{
private:
	/// <summary>
	/// Donn�es contenant les r�sultats apr�s la r�solution
	/// </summary>
	Result * res;

	/// <summary>
	/// Donn�es contenant les param�tres du probl�me � r�soudre
	/// </summary>
	Instance * inst;

public:
	/// <summary>
	/// 1 si j1 est ordonnanc�e avant j2, 0 sinon
	/// </summary>
	vector<vector<bool>> y;

	/// <summary>
	/// 1 si le v�hicule k est utilis�, 0 sinon
	/// </summary>
	vector<bool> Z;

	/// <summary>
	/// 1 si j est transport� par le v�hicule k
	/// </summary>
	vector<vector<bool>> z;

	/// <summary>
	/// 1 si j1 et j2 sont transport�s par un v�hicule k et que j1 est livr� avant j2
	/// </summary>
	vector<vector<vector<bool>>> x;

	/// <summary>
	/// Estimation de la date de livraison de la t�che j
	/// </summary>
	vector<int> D_M;

	/// <summary>
	/// Date de fin de production de la tache j sur une machine m
	/// </summary>
	vector<vector<int>> C;

	/// <summary>
	/// Date de d�part du v�hicule k
	/// </summary>
	vector<int> F;

	/// <summary>
	/// Date de d�part de la tache j
	/// </summary>
	vector<int> f;

	/// <summary>
	/// Estimation du retard pour la tache j pour le producteur
	/// </summary>
	vector<unsigned int> PT_M;

	/// <summary>
	/// Cout d'inventaire total en cours de production
	/// </summary>
	double IC_WIP;

	/// <summary>
	/// Cout d'inventaire total en attente de livraison
	/// </summary>
	double IC_FIN;

	/// <summary>
	/// Cout d'inventaire total
	/// </summary>
	double IC;

	/// <summary>
	/// Pseudo cout de retard du producteur
	/// </summary>
	double PPC_M;

	/// <summary>
	/// Nombre de v�hicule requis par le producteur
	/// </summary>
	int V;

	/// <summary>
	/// Date de livraison de la tache j
	/// </summary>
	vector<int> D_3PL;
	/// <summary>
	/// Retard de la tache J
	/// </summary>
	vector<int> T_M;

	/// <summary>
	/// Cout final des v�hicules
	/// </summary>
	double VC;


	// ==================================================================

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver();

	/// <summary>
	/// Constructeur de la classe Solver
	/// </summary>
	Solver(Instance * instance);

	/// <summary>
	/// Reset les attributs en ins�rant une nouvelle instance
	/// </summary>
	/// <param name="instance"></param>
	void setNewInstance(Instance* instance);

	/// <summary>
	/// Abstract method to solve the problem
	/// </summary>
	/// <returns></returns>
	virtual Result Solve() = 0;
};

