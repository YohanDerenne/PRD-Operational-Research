#include "PSO.h"



double generateDouble(double inf, double sup) {
	double f = (double)rand() / RAND_MAX;
	return inf + f * (sup - inf);
}

PSO::PSO(Instance newInst, double nbSec, int newNbPart) : Solver(newInst, nbSec),
bestParticule(inst), reference(inst)
{
	if (newNbPart < 3) {
		assert(!"3 particules minimum !");
	}
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
	bestParticule.resultatDecode.nb_part = nbPart;
	bestParticule.resultatDecode.cout_ref = GetReference().cout_total;
	return bestParticule.resultatDecode;
}

void PSO::Init()
{
	// Inititalisation des particules
	InitReferences();
	int i = 0;
	for (i = particules.size() - 1; i < nbPart; i++) {
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
	nbPart = i;

	// Décoder toutes les solutions de chaque particule initialisée
	for (int i = 0; i < nbPart; i++) {
		particules[i].Decode();
	}

	// Améliorer la qualité des particules en se basant sur des propriétés dérivés voisines
	for (int i = 0; i < nbPart; i++) {
		particules[i] = ChercherMeilleurVoisin(particules[i]);
	}

	// Garder la meilleure solution
	double bestCost = 9999999999999;
	for (int i = 0; i < nbPart; i++) {
		if (particules[i].resultatDecode.cout_total < bestCost) {
			bestCost = particules[i].resultatDecode.cout_total;
			bestParticule = particules[i];
		}
	}	
}


bool comparator(SolutionPSO i, SolutionPSO j) { return (i.resultatDecode.cout_total < j.resultatDecode.cout_total); }

void PSO::InitReferences()
{
	SolutionPSO ref1 = SolutionPSO(inst);
	SolutionPSO ref2 = SolutionPSO(inst);
	SolutionPSO ref3 = SolutionPSO(inst);
	SolutionPSO ref4 = SolutionPSO(inst);
	SolutionPSO ref5 = SolutionPSO(inst);
	SolutionPSO ref6 = SolutionPSO(inst);
	for (int dj : inst.d) {
		ref1.sv1.push_back((double)dj);
		ref2.sv1.push_back((double)dj);
		ref3.sv1.push_back((double)dj);
	}
	for (int j = 0; j < inst.n; j++){
		double sum = 0;
		for (int i = 0; i < inst.m; i++) {
			sum += inst.p[i][j];
		}
		ref4.sv1.push_back(sum);
		ref5.sv1.push_back(sum);
		ref6.sv1.push_back(sum);
	}
	for (int i = 0; i < inst.n; i++) {
		ref1.sv2.push_back((double)((int)((i + 1) / 4)));
		ref2.sv2.push_back((double)((int)((i + 1) / 3)));
		ref3.sv2.push_back((double)((int)((i + 1) / 5)));
		ref4.sv2.push_back((double)((int)((i + 1) / 4)));
		ref5.sv2.push_back((double)((int)((i + 1) / 3)));
		ref6.sv2.push_back((double)((int)((i + 1) / 5)));
	}
	particules.push_back(ref1);
	particules.push_back(ref2);
	particules.push_back(ref3);
	particules.push_back(ref4);
	particules.push_back(ref5);
	particules.push_back(ref6);
	for (int i = 0; i < particules.size(); i++) {
		particules[i].sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 0));

		// Velocité à 0
		particules[i].velSv1 = vector<double>(inst.n, 0.0);
		particules[i].velSv2 = vector<double>(inst.n, 0.0);
		particules[i].velSv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 0.0));

		particules[i].CDcoef = 0;

		particules[i].Decode();
	}
	SolutionPSO bestRef = *std::min_element(particules.begin(), particules.end(), comparator);
	bestRef.DecodeXY();
	reference = bestRef.resultatDecode;
}


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

	SolutionPSO voisin = VoisinSwitchsv1sv2(sol);
	if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
		bestVoisin = voisin;

	voisin = VoisinSv1Bloc(sol);
	if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
		bestVoisin = voisin;	

	voisin = VoisinIdleNext(sol);
	if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
		bestVoisin = voisin;

	/*
voisin = VoisinAleaIdle(sol);
if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
	bestVoisin = voisin;


	voisin = VoisinMelangeSv2(sol);
	if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
		bestVoisin = voisin;
	*/


	return bestVoisin;
}

SolutionPSO PSO::VoisinSwitchsv1sv2(SolutionPSO sol)
{
	SolutionPSO bestVoisin = sol;
	int delta = 2;

	for (int i = 0; i < inst.n - 1; i++) {
		for (int j = i + 1; j < inst.n && abs(j - i) < delta; j++) {
			// Switch sv1 
			SolutionPSO voisin = sol;
			voisin.sv1[i] = sol.sv1[j];
			voisin.sv1[j] = sol.sv1[i];
			voisin.Decode();
			if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
				bestVoisin = voisin;

			// Switch sv2
			if (sol.affectV[i] != sol.affectV[j]) {
				voisin = sol;
				voisin.sv2[i] = sol.sv2[j];
				voisin.sv2[j] = sol.sv2[i];
				voisin.Decode();
				if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
					bestVoisin = voisin;
			}			
		}
	}

	return bestVoisin;
}

SolutionPSO PSO::VoisinSv1Bloc(SolutionPSO sol)
{
	SolutionPSO bestVoisin = sol;
	int delta = 2;

	for (int i = 0; i < inst.n - delta; i++) {		
		SolutionPSO voisin = sol;
		for (int j = i + delta; j < inst.n && abs(j - i) < delta; j++) {			
			voisin.sv1[i] = sol.sv1[j];
			voisin.sv1[j] = sol.sv1[i];
		}
		voisin.Decode();
		if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
			bestVoisin = voisin;

		voisin = sol;
		for (int j = i + delta; j > (i + delta) / 2; j--) {
			voisin.sv1[i] = sol.sv1[j];
			voisin.sv1[j] = sol.sv1[i];
		}
		voisin.Decode();
		if (voisin.resultatDecode.cout_total < bestVoisin.resultatDecode.cout_total)
			bestVoisin = voisin;		
	}

	return bestVoisin;
}

SolutionPSO PSO::VoisinAleaIdle(SolutionPSO sol)
{
	int i = (int) generateDouble(0, inst.m);
	int j = (int) generateDouble(0, inst.n);
	SolutionPSO voisin = sol;

	voisin.sv3[i][j] = max(voisin.sv3[i][j] + generateDouble(-2,2),0.0);

	voisin.Decode();
	if (voisin.resultatDecode.cout_total < sol.resultatDecode.cout_total)
		return voisin;
	else
		return sol;
}

SolutionPSO PSO::VoisinIdleNext(SolutionPSO sol)
{
	SolutionPSO voisin = sol;
	for (int i = 0; i < inst.m; i++) {
		for (int j = 0; j < inst.n;j++) {
			if (i == inst.m - 1) {
				if (inst.h_WIP[i][j] < inst.h_FIN[j]) {
					voisin.sv3[i][j] = 0.0;
				}
			}
			else {
				if (inst.h_WIP[i][j] < inst.h_WIP[i+1][j]) {
					voisin.sv3[i][j] = 0.0;
				}
				else {
					voisin.sv3[i][j] = (voisin.resultatDecode.C[i+1][j] - inst.p[i+1][j] - voisin.sv3[i+1][j] - voisin.resultatDecode.C[i][j]) +
						voisin.sv3[i + 1][j] + voisin.sv3[i][j];
					voisin.sv3[i + 1][j] = 0;
				}
				
			}			
		}
	}
	voisin.Decode();
	if (voisin.resultatDecode.cout_total < sol.resultatDecode.cout_total)
		return voisin;
	else
		return sol;
}

SolutionPSO PSO::VoisinMelangeSv2(SolutionPSO sol)
{
	SolutionPSO voisin = sol;
	random_shuffle(voisin.sv2.begin(), voisin.sv2.end());
	voisin.Decode();
	if (voisin.resultatDecode.cout_total < sol.resultatDecode.cout_total)
		return voisin;
	else
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

Result PSO::GetReference()
{
	if (reference.cout_total == 0) {
		InitReferences();
	}
	return reference;
}

bool PSO::StopCondition()
{
	int nbPareilMax = nbPart / 2;
	int nbPareil = 0;
	double costRef = particules[0].resultatDecode.cout_total;
	for (int i = 1; i < nbPart; i++) {
		if (particules[i].resultatDecode.cout_total == costRef) {
			nbPareil++;
			if (nbPareil > nbPareilMax) {
				sort(particules.begin(), particules.end(), comparator);
				return true;
			}
		}
	}
	return false;
}


