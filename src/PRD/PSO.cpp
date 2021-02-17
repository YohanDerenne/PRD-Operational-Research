#include "PSO.h"
#include <random>
#include <cassert>


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
		int idParticule = 0;
		for (SolutionPSO particule : particules) {
			// Selectionner deux particules aléatoirement avec le poids CD
			SolutionPSO randParticuleA = GetRandomParticuleWithCD();
			SolutionPSO randParticuleB = GetRandomParticuleWithCD();

			// Mise à jour de la velocitésV 
			double lambda1 = generateDouble(0, 1);
			double lambda2 = generateDouble(0, 1);
			double lambda3 = generateDouble(0, 1);
			for (int d = 0; d < particule.velSv1.size(); d++) {
				particule.velSv1[d] = lambda1 * particule.velSv1[d] + 
					lambda2 * (randParticuleA.sv1[d] - particule.sv1[d]) + 
					lambda3 * (randParticuleB.sv1[d] - particule.sv1[d]);
			}
			for (int d = 0; d < particule.velSv2.size(); d++) {
				particule.velSv2[d] = lambda1 * particule.velSv2[d] +
					lambda2 * (randParticuleA.sv2[d] - particule.sv2[d]) +
					lambda3 * (randParticuleB.sv2[d] - particule.sv2[d]);
			}
			for (int i = 0; i < particule.velSv3.size(); i++) {
				for (int j = 0; j < particule.velSv3[i].size(); j++) {
					particule.velSv3[i][j] = lambda1 * particule.velSv3[i][j] +
						lambda2 * (randParticuleA.sv3[i][j] - particule.sv3[i][j]) +
						lambda3 * (randParticuleB.sv3[i][j] - particule.sv3[i][j]);
				}
			}			

			// Mise à jour de la position des particules
			for (int d = 0; d < particule.sv1.size(); d++) {
				particule.sv1[d] = particule.sv1[d] + particule.velSv1[d];
			}
			for (int d = 0; d < particule.sv2.size(); d++) {
				particule.sv2[d] = particule.sv2[d] + particule.velSv2[d];
			}
			for (int i = 0; i < particule.sv3.size(); i++) {
				for (int j = 0; j < particule.sv3[i].size(); j++) {
					particule.sv3[i][j] = particule.sv3[i][j] + particule.velSv3[i][j];
				}
			}

			// Decoder la solution complete de la particule
			particule.Decode();

			// Améliorer la qualité de la particule basé sur des propriétés dérivés voisines
			particule = ChercherMeilleurVoisin(particule);
			particules[idParticule] = particule; // save in particule vector

			//Garder la solution trouvée si celle-ci est la meilleure jamais trouvée
			if (particule.resultatDecode.cout_total < bestParticule.resultatDecode.cout_total) {
				bestParticule = particule;
			}

			idParticule++;
		}

		// Mise à jour du temps écoulé
		tempsEcoule = difftime(time(0), debut);
	}

	bestParticule.resultatDecode.dureeSec = dureeMax;
	return bestParticule.resultatDecode;
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
	int i = 0;
	for (SolutionPSO particule : particules) {
		SolutionPSO voisin = ChercherMeilleurVoisin(particule);
		if (voisin.resultatDecode.cout_total < particule.resultatDecode.cout_total)
			particules[i] = voisin;
		if (voisin.resultatDecode.cout_total < bestCost) {
			bestCost = voisin.resultatDecode.cout_total;
			bestParticule = voisin;
		}
		i++;
	}
}

bool comparator(SolutionPSO i, SolutionPSO j) { return (i.resultatDecode.cout_total < j.resultatDecode.cout_total); }

void PSO::CalculCrowdingDistance()
{
	// Decoder chaque particule et mettre les CD à 0
	for (SolutionPSO particule : particules) {
		particule.Decode();
		particule.CDcoef = 0;
	}

	// Trier les particules par ordre croissant
	sort(particules.begin(), particules.end(), comparator);

	double fmin = particules[0].resultatDecode.cout_total;
	double fmax = particules[nbPart - 1].resultatDecode.cout_total;

	particules[0].CDcoef += 1;
	particules[nbPart - 1].CDcoef += 1;

	for (int i = 1; i < nbPart - 2; i++) {
		particules[i].CDcoef = particules[i].CDcoef + 
			(particules[i + 1].resultatDecode.cout_total - particules[i - 1].resultatDecode.cout_total) / (fmax - fmin);
	}
}

SolutionPSO PSO::ChercherMeilleurVoisin(SolutionPSO sol)
{
	return sol;
}

SolutionPSO PSO::GetRandomParticuleWithCD()
{
	double poidsTotal = 0;
	for (int i = 0; i < nbPart; i++) {
		poidsTotal += particules[i].CDcoef;
	}
	double rnd = generateDouble(0, poidsTotal);
	for (int i = 0; i < nbPart; i++) {
		if (rnd < particules[i].CDcoef)
			return  particules[i];
		rnd -= particules[i].CDcoef;
	}
	assert(!"Ne dois pas arriver ici");
}


