#include "PSO.h"
#include <time.h>

double generateDouble(double inf, double sup) {
	double f = (double)rand() / RAND_MAX;
	return inf + f * (sup - inf);
}

PSO::PSO(Instance newInst, double nbSec, int newNbPart) : Solver(newInst, nbSec),
bestParticule(inst)
{
	bestParticule = SolutionPSO(newInst);
	nbPart = newNbPart;
}

Result PSO::Solve()
{
	// D�clenchement du chrono
	double tempsEcoule = 0;
	time_t debut = time(0);

	// Init particules
	Init();

	// Boucle Principale
	while (tempsEcoule < dureeMax) {

		// Decoder les solutions de chaque particule et calculer la Crowding Distance (CD)
		CalculCrowdingDistance();

		// Pour chaque particule
		for (SolutionPSO particule : particules) {
			// Selectionner deux particules al�atoirement avec le poids CD

			// Mise � jour de la velocit�sV ppuis de la positionXpde la particule 

			// Decoder la solution complete de la particule

			// Am�liorer la qualit� de la particule bas� sur des propri�t�s d�riv�s voisines

			//Garder la solution trouv�e si celle-ci est la meilleure jamais trouv�e

		}

		// Mise � jour du temps �coul�
		tempsEcoule = difftime(time(0), debut);
	}

	return Result(inst);
}

void PSO::Init()
{
	// Inititalisation des particules
	for (int i = 0; i < nbPart; i++) {
		SolutionPSO part = SolutionPSO(inst);

		// Sv1 ini al�atoire entre -1 et 1
		part.sv1 = vector<double>(inst.n, 0.0);		
		for (int j = 0; j < part.sv1.size(); j++) {
			part.sv1[j] = generateDouble(-1,1);
		}

		// Sv2 ini al�atoire entre -0.5 et m-0.5
		part.sv2 = vector<double>(inst.n, 0.0);
		for (int j = 0; j < part.sv2.size(); j++) {
			part.sv2[j] = generateDouble(-0.5, inst.m - 0.5);
		}

		// Sv3 ini al�atoire entre 0 et 50
		part.sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 0.0));
		for (int j = 0; j < part.sv3.size(); j++) {
			for (int k = 0; k < part.sv3[j].size(); k++) {
				part.sv3[j][k] = generateDouble(0, 50);
			}
		}

		// Velocit� � 0
		part.velSv1 = vector<double>(inst.n, 0.0);
		part.velSv2 = vector<double>(inst.n, 0.0);
		part.velSv3 = vector<vector<double>>(inst.m , vector<double>(inst.n, 0.0));

		particules.push_back(part);
	}

	// D�coder toutes les solutions de chaque particule initialis�e
	for (SolutionPSO particule : particules) {
		particule.Decode();
	}

	// Garder la meilleure solution
	double bestCost = 9999999999999;
	for (SolutionPSO particule : particules) {
		if (particule.resultatDecode.cout_total < bestCost) {
			bestCost = particule.resultatDecode.cout_total;
			bestParticule = particule;
		}
	}

	// Am�liorer la qualit� des particules en se basant sur des propri�t�s d�riv�s voisines
	// Garder la solution si elle est mieux

}

void PSO::CalculCrowdingDistance()
{
}

SolutionPSO PSO::ChercherMeilleurVoisin(SolutionPSO sol)
{
	return sol;
}


