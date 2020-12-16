#pragma once
#include <vector> 
#include <string>
using namespace std;

class Instance
{
public :

	// ============================== PARAMETRES ===================================

	/// <summary>
	/// Index de l'instance
	/// </summary>
	int id;

	/// <summary>
	/// Nombre de commandes
	/// </summary>
	int n;
	
	/// <summary>
	/// Nombre de machines
	/// </summary>
	int m;

	/// <summary>
	/// Temps de production d'une tache i sur une machine j
	/// </summary>
	vector<vector<int>> p;

	/// <summary>
	/// Date de livraison d'une commande i
	/// </summary>
	vector<int> d;

	/// <summary>
	/// Distance entre un site i et un site j
	/// </summary>
	vector<vector<int>> t;

	/// <summary>
	/// Tr�s grande valeur arbitraire
	/// </summary>
	int HV = 999999999;

	/// <summary>
	/// Cout d'inventaire d'une t�che i sur une machine j
	/// </summary>
	vector<vector<int>> h_WIP;

	/// <summary>
	/// Cout d'inventaire d'une commande i en fin de production
	/// </summary>
	vector<int> h_FIN;

	/// <summary>
	/// Cout de p�nalit� si une commande i est livr�e en retard
	/// </summary>
	vector<int> p_M;

	/// <summary>
	/// Cout d'un v�hicule
	/// </summary>
	int c_V;

	// ============================== METHODES ===================================

	/// <summary>
	/// Constructeur de la classe Instance
	/// </summary>
	Instance() {};

	/// <summary>
	/// Constructeur de la classe Instance qui parse un fichier txt contenant une instance
	/// </summary>
	/// <param name="path">Emplacement du fichier txt</param>
	Instance(string path);

	/// <summary>
	/// Parse un fichier txt qui contient une instance
	/// </summary>
	/// <param name="path">Emplacement du fichier txt</param>
	/// <returns>Status (true = erreur)</returns>
	bool Parse(string path);
};

