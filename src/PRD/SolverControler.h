#pragma once
#include "Solver.h"
#include <list>


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
	list<Instance*> instances;

	/// <summary>
	/// Resultats des algos
	/// </summary>
	list<Result*> results;

public:
	/// <summary>
	/// Construteur du controleur
	/// </summary>
	SolverControler();

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
	void Reset();

	// ================================== Get / Set =================================

	const list<Instance*> getInstances() { return instances; }
	const list<Result*> getResults() { return results; }
	void AddResult(Result* res) { results.push_back(new Result(*res)); }
};
