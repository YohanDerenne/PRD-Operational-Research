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

	/// <summary>
	/// Resultat de la solution apr�s avoir d�coder les vecteurs
	/// </summary>
	Result resultatDecode;

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les r�sultats. 
	/// ATTENTION : ne d�code pas x et y
	/// </summary>
	/// <returns>Le r�sultats d�cod�</returns>
	Result Decode();

	/// <summary>
	/// Instance de la solution
	/// </summary>
	Instance inst;

	/// <summary>
	/// Constructeur avec instance pour parametre
	/// </summary>
	/// <param name="instance">Instance sur laquelle la solution se base</param>
	Solution(Instance instance);

	/// <summary>
	/// Decode les vecteurs x et y, mais celui ci n'est pas necessaire pour l'algoithme, seulement pour la v�rification. 
	/// Complexite n^3, � utiliser avec parsimonie.
	/// </summary>
	void DecodeXY();
};

