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
	/// Vecteur qui contient l'affectation des v�hicules
	/// </summary>
	vector<double> sv2;
	/// <summary>
	/// Vecteur qui contient les temps morts
	/// </summary>
	vector<vector<double>> sv3;

	/// <summary>
	/// Index de la tache qui se trouve � la position x de l'ordonnancement
	/// </summary>
	vector<int> ordre;
	/// <summary>
	/// Num�ro de v�hicule utilis� par la tache j
	/// </summary>
	vector<int> affectV;
	/// <summary>
	/// Dur�e d'attente d'une tache j sur une machine i
	/// </summary>
	vector<vector<double>> idle;

	Result resultatDecode;

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les r�sultats
	/// </summary>
	/// <param name="inst"></param>
	/// <returns></returns>
	Result Decode();

	Instance inst;

	Solution(Instance instance);

	void DecodeXY();
};

