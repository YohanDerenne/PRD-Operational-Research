#pragma once
#include "Solver.h"
#include <list>


class SolverControler
{
private:
	/// <summary>
	/// Classe permettant la résolution du problème d'ordonnancement
	/// </summary>
	Solver* solver;

	/// <summary>
	/// Instances à étudier
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

	~SolverControler();

	/// <summary>
	/// Boucle principal permettant la résolution du probleme sur chaque instances importés
	/// </summary>
	void LaunchComputation();

	/// <summary>
	/// Importe toutes les instances présentes dans un dossier
	/// </summary>
	/// <param name="dir">Chemin du dossier contenant les instances</param>
	/// <returns>Status</returns>
	bool ImportInstances(string dir);

	/// <summary>
	/// Exporte les résultats dans un dossier
	/// </summary>
	/// <param name="path">Chemin du dossier de sauvegarde des résultats</param>
	/// <returns>Status</returns>
	bool ExportResults(string path);
	
};

