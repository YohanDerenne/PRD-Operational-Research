#include "Result.h"

Result::Result(Instance instance):y(),Z(),z(),x(),D_M(),C(),F(),f(),PT_M(),D_3PL(),T_M()
{
	
	V = 0;
	cout_total = 0;
	nb_part = 0;

	inst = Instance(instance);


	IC_WIP = 0;
	IC_FIN = 0;
	IC = 0;
	PPC_M = 0;
	VC = 0;
	cout_ref = 0;
	dureeSec = 0.0;
}

Result::Result():y(), Z(), z(), x(), D_M(), C(), F(), f(), PT_M(), D_3PL(), T_M()
{
	V = 0;
	cout_total = 0;
	nb_part = 0;

	IC_WIP = 0;
	IC_FIN = 0;
	IC = 0;
	PPC_M = 0;

	cout_ref = 0;
	VC = 0;

	dureeSec = 0.0;
}

Result::Result(const Result& result) :y(), Z(), z(), x(), D_M(), C(), F(), f(), PT_M(), D_3PL(), T_M()
{
	inst = Instance(result.inst),
	V = result.V;
	cout_total = result.cout_total;
	nb_part = result.nb_part;

	IC_WIP = result.IC_WIP;
	IC_FIN = result.IC_FIN;
	IC = result.IC;
	PPC_M = result.PPC_M;

	cout_ref = result.cout_ref;
	VC = result.VC;

	dureeSec = result.dureeSec;

	y = vector<vector<bool>>(result.y);
	Z = vector<bool>(result.Z);
	z = vector<vector<bool>>(result.z);
	x = vector<vector<vector<bool>>>(result.x);
	D_M = vector<double>(result.D_M);
	C = vector<vector<double>>(result.C);
	F = vector<double>(result.F);
	f = vector<double>(result.f);
	PT_M = vector<double>(result.PT_M);
	D_3PL = vector<double>(result.D_3PL);
	T_M = vector<double>(result.T_M);
}


bool Result::VerificationContraintes()
{
	double HV = DBL_MAX;

	// Une contrainte relative à l’ordre des tâches (une tâche ne peut pas être produit à la fois avant et après une autre)
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int j2 = j1 + 1; j2 < inst.n; j2++) {
			if (y[j1][j2] + y[j2][j1] != 1)
				return false;
		}
	}

	// Contrainte pour dire qu’une tâche ne peut pas entrer en production sur une machine avant que celle - ci ne soit libre :
	for (int i = 0; i < inst.m; i++) {
		for (int j1 = 0; j1 < inst.n; j1++) {
			for (int j2 = 0; j2 < inst.n; j2++) {
				if (j1 == j2)
					continue;
				if (C[i][j2] < C[i][j1] + inst.p[i][j2] - HV * (1 - (double) y[j1][j2]))
					return false;
			}
		}
	}

	// Contrainte indiquant que chaque job doit passer dans chaque machine dans l’ordre :
	for (int i = 1; i < inst.m; i++) {
		for (int j = 0; j< inst.n; j++) {
			if (C[i][j] < C[i-1][j] + inst.p[i][j])
				return false;
		}
	}

	// Chaque commande doit être transportée dans un véhicule :
	for (int j = 0; j < inst.n; j++) {
		int sum = 0;
		for (int k = 0; k < inst.n; k++) {
			sum += (int) z[j][k];
		}
		if (sum != 1)
			return false;
	}

	// Chaque véhicule ne peut partir que si les commandes qu’il doit transporter sont produites :
	for (int k = 0; k < inst.n; k++) {
		for (int j = 0; j < inst.n; j++) {
			if (F[k] < C[inst.m - 1][j] - HV * (1 - (double) z[j][k]))
				return false;
		}
	}

	// Une commande ne peut pas être livrée tant qu’elle n’est pas produite :
	for (int j = 0; j < inst.n; j++) {
		for (int k = 0; k < inst.n; k++) {
			if (f[j] < F[k] - HV * (1 - (double)z[j][k]))
				return false;
		}
	}

	// Un véhicule k est utilisé à partir du moment où il doit transporter au moins une commande :
	for (int k = 0; k < inst.n; k++) {
		int sum = 0;
		for (int j = 0; j < inst.n; j++) {
			sum += (int)z[j][k];
		}
		if (HV * Z[k] < sum)
			return false;
	}

	// TODO Dans un même lot, un job j1 a un prédécesseur j2 avec un seuil de livraison inférieur, sinon le
	// prédécesseur est le site de production
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int k = 0; k < inst.n; k++) {
			// TODO
		}
	}
	
	/*
	//Pour le routage d’un véhicule k, le site de production a un successeur seulement si le véhicule k est utilisé :
	for (int k = 0; k < inst.n; k++) {
		int sum = 0;
		for (int j = 0; j < inst.n; j++) {
			sum += x[0][j][k];
		}
		if (sum > Z[k])
			return false;//here
	}
	*/

	// L’estimation de la date de livraison est donnée via cette contrainte :
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int j2 = j1 + 1; j2 < inst.n; j2++) {
			for (int k = 0; k < inst.n; k++) {
				if (D_M[j2] < D_M[j1] + inst.t[j1 + 2][j2 + 2] - HV * (1 - (double)x[j1][j2][k]))
					return false;
			}
		}
	}

	// Contrainte donnant une borne inférieure sur la date de livraison d’une tâche j transporté par un véhicule k :
	for (int j = 0; j < inst.n; j++) {
		for (int k = 0; k < inst.n; k++) {
			if (D_M[j] < F[k] + inst.t[0][j+2] - HV * (1 - (double)z[j][k]))
				return false; // here
		}
	}

	// Estimation du retard d’un job :
	for (int j = 0; j < inst.n; j++) {
		if (PT_M[j] < D_M[j] - inst.d[j])
			return false;
	}

	// Toutes les contraintes sont respectées
	return true;
}
