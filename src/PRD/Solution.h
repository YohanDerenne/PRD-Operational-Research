#pragma once

#include "Result.h"

class Solution
{
public :
	vector<double> sv1;
	vector<double> sv2;
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

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les résultats
	/// </summary>
	/// <param name="inst"></param>
	/// <returns></returns>
	Result* Decode(Instance * inst);
};

