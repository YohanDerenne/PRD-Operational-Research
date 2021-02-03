#pragma once

#include "Result.h"

class Solution
{
public :
	vector<double> sv1;
	vector<double> sv2;
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

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les r�sultats
	/// </summary>
	/// <param name="inst"></param>
	/// <returns></returns>
	Result* Decode(Instance * inst);
};

