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
	// Déclenchement du chrono
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
			// Selectionner deux particules aléatoirement avec le poids CD

			// Mise à jour de la velocitésV ppuis de la positionXpde la particule 

			// Decoder la solution complete de la particule

			// Améliorer la qualité de la particule basé sur des propriétés dérivés voisines

			//Garder la solution trouvée si celle-ci est la meilleure jamais trouvée

		}

		// Mise à jour du temps écoulé
		tempsEcoule = difftime(time(0), debut);
	}

	return Result(inst);
}

void PSO::Init()
{
	// Inititalisation des particules
	for (int i = 0; i < nbPart; i++) {
		SolutionPSO part = SolutionPSO(inst);

		// Sv1 ini aléatoire entre -1 et 1
		part.sv1 = vector<double>(inst.n, 0.0);		
		for (int j = 0; j < part.sv1.size(); j++) {
			part.sv1[j] = generateDouble(-1,1);
		}

		// Sv2 ini aléatoire entre -0.5 et m-0.5
		part.sv2 = vector<double>(inst.n, 0.0);
		for (int j = 0; j < part.sv2.size(); j++) {
			part.sv2[j] = generateDouble(-0.5, inst.m - 0.5);
		}

		// Sv3 ini aléatoire entre 0 et 50
		part.sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 0.0));
		for (int j = 0; j < part.sv3.size(); j++) {
			for (int k = 0; k < part.sv3[j].size(); k++) {
				part.sv3[j][k] = generateDouble(0, 50);
			}
		}

		// Velocité à 0
		part.velSv1 = vector<double>(inst.n, 0.0);
		part.velSv2 = vector<double>(inst.n, 0.0);
		part.velSv3 = vector<vector<double>>(inst.m , vector<double>(inst.n, 0.0));

		particules.push_back(part);
	}

	// Décoder toutes les solutions de chaque particule initialisée
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

	// Améliorer la qualité des particules en se basant sur des propriétés dérivés voisines
	// Garder la solution si elle est mieux

}

void PSO::CalculCrowdingDistance()
{
}

SolutionPSO PSO::ChercherMeilleurVoisin(SolutionPSO sol)
{
	return sol;
}


