#pragma once
#include "Solver.h"
#include <list>

/// <summary>
/// Determine si un fichier du meme nom existe
/// </summary>
/// <param name="name">Nom du fichier � v�rifier</param>
/// <returns>1 pour oui, 0 sinon</returns>
bool fileExist(const std::string& name);

/// <summary>
/// V�rifie si la chaine se termine avec un suffixe
/// </summary>
/// <param name="str">La chaine � comparer</param>
/// <param name="suffix">Suffixe recherch� � la fin de la chaine</param>
/// <returns>True pour oui</returns>
bool has_suffix(const std::string& str, const std::string& suffix);

/// <summary>
/// Convertie un char* en whar_t*
/// </summary>
/// <param name="charArray">Chaine � convertir</param>
/// <returns>Chaine convertie</returns>
wchar_t* charArrayToLPCWSTR(const char* charArray);

/// <summary>
/// Convertie un wchar_t* en string
/// </summary>
/// <param name="txt">Chaine � convertir</param>
/// <returns>Chaine convertie</returns>
string LPCWSTRtoString(wchar_t* txt);

class SolverControler
{
private:
	/// <summary>
	/// Classe permettant la r�solution du probl�me d'ordonnancement
	/// </summary>
	Solver* solver;

	/// <summary>
	/// Instances � �tudier
	/// </summary>
	list<Instance> instances;

	/// <summary>
	/// Resultats des algos
	/// </summary>
	list<Result> results;

public:
	/// <summary>
	/// Construteur du controleur
	/// </summary>
	SolverControler();

	/// <summary>
	/// Contructeur avec parametre
	/// </summary>
	SolverControler(Solver* sol);

	~SolverControler();

	/// <summary>
	/// Boucle principal permettant la r�solution du probleme sur chaque instances import�s
	/// </summary>
	void LaunchComputation();

	/// <summary>
	/// Importe toutes les instances pr�sentes dans un dossier
	/// </summary>
	/// <param name="dir">Chemin du dossier contenant les instances</param>
	/// <returns>Status</returns>
	bool ImportInstances(string dir);

	/// <summary>
	/// Exporte les r�sultats dans un dossier
	/// </summary>
	/// <param name="path">Chemin du dossier de sauvegarde des r�sultats</param>
	/// <returns>Status</returns>
	bool ExportResults(string path);

	/// <summary>
	/// Reset les attributs de la classe
	/// </summary>
	void Reset(Solver * newSolver);

	// ================================== Get / Set =================================

	/// <summary>
	/// Recupere la liste des instances
	/// </summary>
	/// <returns>Liste des instances</returns>
	const list<Instance> getInstances() { return instances; }

	/// <summary>
	/// Recupere la liste des resultats
	/// </summary>
	/// <returns>Liste des r�sultats</returns>
	const list<Result> getResults() { return results; }

	/// <summary>
	/// Permet d'ajouter un resultat
	/// </summary>
	/// <param name="res">Resultat � ajouter</param>
	void AddResult(Result res) { results.push_back(Result(res)); }
};

