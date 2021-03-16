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

	/// <summary>
	/// Resultat de la solution après avoir décoder les vecteurs
	/// </summary>
	Result resultatDecode;

	/// <summary>
	/// Decode les vecteurs de la solutions et renvoie les résultats. 
	/// ATTENTION : ne décode pas x et y
	/// </summary>
	/// <returns>Le résultats décodé</returns>
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
	/// Decode les vecteurs x et y, mais celui ci n'est pas necessaire pour l'algoithme, seulement pour la vérification. 
	/// Complexite n^3, à utiliser avec parsimonie.
	/// </summary>
	void DecodeXY();
};

