#include "PSO.h"
#include <time.h>

PSO::PSO(Instance * newInst, double nbSec, int newNbPart) : Solver(newInst, nbSec)
{
	nbPart = newNbPart;
}

Result* PSO::Solve()
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
		for (SolutionPSO particule : paticules) {

		}

		// Mise à jour du temps écoulé
		tempsEcoule = difftime(time(0), debut);
	}

	return nullptr;
}

void PSO::Init()
{
}

void PSO::CalculCrowdingDistance()
{
}

SolutionPSO PSO::ChercherMeilleurVoisin()
{
}
