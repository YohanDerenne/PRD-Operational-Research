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
	/// Temps de production d'une tache j sur une machine i
	/// </summary>
	vector<vector<double>> p;

	/// <summary>
	/// Date de livraison d'une commande i
	/// </summary>
	vector<int> d;

	/// <summary>
	/// <para>Distance entre un site i et un site j</para>
	/// <para>ATTENTION : </para>
	/// <para>indice 0 -> d�pot production</para>
	/// <para>indice 1 -> d�pot distribution</para>
	/// <para>les autres indices -> lieu de livraison des jobs (2 -> job 0, 3 -> job 1 ,...)</para>
	/// </summary>
	vector<vector<int>> t;

	/// <summary>
	/// Tr�s grande valeur arbitraire
	/// </summary>
	int HV = 999999999;

	/// <summary>
	/// Cout d'inventaire d'une t�che j sur une machine i
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
	Instance();

	/// <summary>
	/// Constructeur de la classe Instance qui parse un fichier txt contenant une instance
	/// </summary>
	/// <param name="path">Emplacement du fichier txt</param>
	Instance(string path);

	/// <summary>
	/// Constructeur de copie de la classe Instance
	/// </summary>
	/// <param name="inst2"></param>
	Instance(const Instance& inst2);

	/// <summary>
	/// Parse un fichier txt qui contient une instance
	/// </summary>
	/// <param name="path">Emplacement du fichier txt</param>
	/// <returns>Status (true = erreur)</returns>
	bool Parse(string path);
};

