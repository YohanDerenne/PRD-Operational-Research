#pragma once
#include "Instance.h"
class Result
{
public :

	// ============================= DATA ====================================

	/// <summary>
	/// Instance sur laquelle s'appuie les r�sultats
	/// </summary>
	Instance * inst;

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

	double cout_total;

	// ============================== METHODES ===================================

	/// <summary>
	/// Constructeur de la classe Resultat
	/// </summary>
	/// <param name="instance"></param>
	Result(Instance * instance);

	/// <summary>
	/// Constructeur de copie de la classe Resultat
	/// </summary>
	/// <param name="res2"></param>
	Result(const Result& res2);

	~Result();
};

