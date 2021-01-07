#pragma once
#include "Instance.h"
class Result
{
public :

	// ============================= DATA ====================================

	/// <summary>
	/// Instance sur laquelle s'appuie les résultats
	/// </summary>
	Instance * inst;

	/// <summary>
	/// Cout total après résolution
	/// </summary>
	double cout_total;

	/// <summary>
	/// Somme des couts d'inventaire en cours de production après résolution
	/// </summary>
	double cout_WIP;

	/// <summary>
	/// Somme des couts d'inventaire en attente de livraison après résolution
	/// </summary>
	double cout_FIN;

	/// <summary>
	/// Somme des couts de retard après résolution
	/// </summary>
	double cout_retard;

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
	Result(Result& res2);
};

