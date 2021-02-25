#pragma once

#include "Result.h"

class Solution
{
public :
	/// <summary>
	/// Vecteur qui contient l'ordonnacement
	/// </summary>
	vector<double> sv1;
	/// <summary>
	/// Vecteur qui contient l'affectation des véhicules
	/// </summary>
	vector<double> sv2;
	/// <summary>
	/// Vecteur qui contient les temps morts
	/// </summary>
	vector<vector<double>> sv3;

	/// <summary>
	/// Index de la tache qui se trouve à la position x de l'ordonnancement
	/// </summary>
	vector<int> ordre;
	/// <summary>
	/// Numéro de véhicule utilisé par la tache j
	/// </summary>
	vector<int> affectV;
	/// <summary>
	/// Durée d'attente d'une tache j sur une machine i
	/// </summary>
	vector<vector<double>> idle;

	Result resultatDecode;

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les résultats
	/// </summary>
	/// <param name="inst"></param>
	/// <returns></returns>
	Result Decode();

	Instance inst;

	Solution(Instance instance);

	void DecodeXY();
};

