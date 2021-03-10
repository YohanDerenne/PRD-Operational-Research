#include "PSO.h"



double generateDouble(double inf, double sup) {
	double f = (double)rand() / RAND_MAX;
	return inf + f * (sup - inf);
}

PSO::PSO(Instance newInst, double nbSec, int newNbPart) : Solver(newInst, nbSec),
bestParticule(inst)
{
	if (newNbPart < 3) {
		assert(!"3 particules minimum !");
	}
	bestParticule = SolutionPSO(newInst);
	nbPart = newNbPart;
}

Result PSO::Solve()
{
	// Déclenchement du chrono
	double tempsEcoule = 0;
	chrono::system_clock::time_point debut = chrono::system_clock::now();

	// Init particules
	Init();

	// Boucle Principale
	while (tempsEcoule < dureeMax && !StopCondition()) {
		// Prendre le mini 

		// Decoder les solutions de chaque particule et calculer la Crowding Distance (CD)
		CalculCrowdingDistance();
		
		//particules[0] = bestParticule;
		//particules[0].CDcoef = 1;

		// Pour chaque particule
		for (int p = 0; p < nbPart; p++) {
			// Selectionner deux particules aléatoirement avec le poids CD
			SolutionPSO randParticuleA = GetRandomParticuleWithCD();
			SolutionPSO randParticuleB = GetRandomParticuleWithCD();

			// Mise à jour de la velocitésV 
			double lambda1 = generateDouble(0, 1);
			double lambda2 = generateDouble(0, 1);
			double lambda3 = generateDouble(0, 1);

			//modif JCB
			/*
			lambda1 = 0.5;
			lambda2 = 0.5;
			lambda3 = 0.5;
			*/

			for (int d = 0; d < particules[p].velSv1.size(); d++) {
				particules[p].velSv1[d] = lambda1 * particules[p].velSv1[d] +
					lambda2 * (randParticuleA.sv1[d] - particules[p].sv1[d]) +
					lambda3 * (randParticuleB.sv1[d] - particules[p].sv1[d]);
			}
			for (int d = 0; d < particules[p].velSv2.size(); d++) {
				particules[p].velSv2[d] = lambda1 * particules[p].velSv2[d] +
					lambda2 * (randParticuleA.sv2[d] - particules[p].sv2[d]) +
					lambda3 * (randParticuleB.sv2[d] - particules[p].sv2[d]);
			}
			for (int i = 0; i < particules[p].velSv3.size(); i++) {
				for (int j = 0; j < particules[p].velSv3[i].size(); j++) {
					particules[p].velSv3[i][j] = lambda1 * particules[p].velSv3[i][j] +
						lambda2 * (randParticuleA.sv3[i][j] - particules[p].sv3[i][j]) +
						lambda3 * (randParticuleB.sv3[i][j] - particules[p].sv3[i][j]);
				}
			}			

			// Mise à jour de la position des particules
			for (int d = 0; d < particules[p].sv1.size(); d++) {
				particules[p].sv1[d] = particules[p].sv1[d] + particules[p].velSv1[d];
			}
			for (int d = 0; d < particules[p].sv2.size(); d++) {
				particules[p].sv2[d] = particules[p].sv2[d] + particules[p].velSv2[d];
			}
			for (int i = 0; i < particules[p].sv3.size(); i++) {
				for (int j = 0; j < particules[p].sv3[i].size(); j++) {
					particules[p].sv3[i][j] = particules[p].sv3[i][j] + particules[p].velSv3[i][j];
				}
			}

			// Decoder la solution complete de la particule
			particules[p].Decode();

			// Améliorer la qualité de la particule basé sur des propriétés dérivés voisines
			particules[p] = ChercherMeilleurVoisin(particules[p]);

			//Garder la solution trouvée si celle-ci est la meilleure jamais trouvée
			if (particules[p].resultatDecode.cout_total < bestParticule.resultatDecode.cout_total) {
				bestParticule = particules[p];
			}
		}		

		// Mise à jour du temps écoulé
		std::chrono::duration<double> elapsed_seconds = chrono::system_clock::now() - debut;
		tempsEcoule = elapsed_seconds.count();
	}
	dureeResolution = tempsEcoule;
	bestParticule.DecodeXY();
	bestParticule.resultatDecode.dureeSec = tempsEcoule;
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

		part.CDcoef = 0;

		particules.push_back(part);
	}

	// Décoder toutes les solutions de chaque particule initialisée
	for (int i = 0; i < nbPart; i++) {
		particules[i].Decode();
	}

	// Garder la meilleure solution
	double bestCost = 9999999999999;
	for (int i = 0; i < nbPart; i++) {
		if (particules[i].resultatDecode.cout_total < bestCost) {
			bestCost = particules[i].resultatDecode.cout_total;
			bestParticule = particules[i];
		}
	}

	// Améliorer la qualité des particules en se basant sur des propriétés dérivés voisines
	for (int i = 0; i < nbPart; i++) {
		SolutionPSO voisin = ChercherMeilleurVoisin(particules[i]);
		if (voisin.resultatDecode.cout_total < particules[i].resultatDecode.cout_total)
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
	for (int i = 0; i < nbPart; i++) {
		//particules[i].Decode();
		particules[i].CDcoef = 0;
	}

	// Trier les particules par ordre croissant
	sort(particules.begin(), particules.end(), comparator);

	double fmin = particules[0].resultatDecode.cout_total;
	double fmax = particules[nbPart - 1].resultatDecode.cout_total;

	particules[0].CDcoef += 1;
	//particules[nbPart - 1].CDcoef += 1;

	for (int i = 1; i < nbPart - 2; i++) {
		// Debug
		if (isnan(particules[i].CDcoef)) {
			break;
		}
		particules[i].CDcoef = particules[i].CDcoef + 
			(particules[i + 1].resultatDecode.cout_total - particules[i - 1].resultatDecode.cout_total) / (fmax - fmin);
		// Debug
		if (isnan(particules[i].CDcoef)) {
			particules[i].CDcoef = 0.000000000001;
		}
	}
}

SolutionPSO PSO::ChercherMeilleurVoisin(SolutionPSO sol)
{
	SolutionPSO bestVoisin = sol;
	int delta = 2;
	
	
	for (int i = 0; i < inst.n - 1; i++) {
		for (int j = i + 1; j < inst.n && abs(j-i) < delta; j++) {
			// Switch sv1 
			SolutionPSO voisin = sol;
			voisin.sv1[i] = sol.sv1[j];
			voisin.sv1[j] = sol.sv1[i];
			voisin.Decode();
			if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
				bestVoisin = voisin;

			// Switch sv2
			voisin = sol;
			voisin.sv2[i] = sol.sv2[j];
			voisin.sv2[j] = sol.sv2[i];
			voisin.Decode();
			if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
				bestVoisin = voisin;
		}
	}
	
	
	


	return bestVoisin;
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

Result PSO::GetReference()
{
	SolutionPSO sol = SolutionPSO(inst);

	for (int dj : inst.d) {
		sol.sv1.push_back((double) dj);
	}

	for (int i = 0; i < inst.m; i++) {
		sol.sv2.push_back((double)((int)((i+1) / 4)));
	}

	sol.sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n,0));
	sol.Decode();
	sol.DecodeXY();
	return sol.resultatDecode;
}

bool PSO::StopCondition()
{
	int nbPareilMax = nbPart / 2;
	int nbPareil = 0;
	double costRef = particules[0].resultatDecode.cout_total;
	for (int i = 1; i < nbPart; i++) {
		if (particules[i].resultatDecode.cout_total == costRef) {
			nbPareil++;
			if (nbPareil > nbPareilMax)
				return true;
		}
	}
	return false;
}


