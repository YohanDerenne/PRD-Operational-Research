#include "Result.h"

Result::Result(Instance instance)
{
	inst = instance;

	y = vector<vector<bool>>();
	Z = vector<bool>();
	z = vector<vector<bool>>();
	x = vector<vector<vector<bool>>>();
	D_M = vector<double>();
	C = vector<vector<double>>();
	F = vector<double>();
	f = vector<double>();
	PT_M = vector<double>();
	IC_WIP = 0;
	IC_FIN = 0;
	IC = 0;
	PPC_M = 0;

	D_3PL = vector<double>();
	T_M = vector<double>();
	VC = 0;

	dureeSec = 0.0;
}

Result::~Result()
{
}

bool Result::VerificationContraintes()
{
	double HV = DBL_MAX;

	// Une contrainte relative � l�ordre des t�ches (une t�che ne peut pas �tre produit � la fois avant et apr�s une autre)
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int j2 = j1 + 1; j2 < inst.n; j2++) {
			if (y[j1][j2] + y[j2][j1] != 1)
				return false;
		}
	}

	// Contrainte pour dire qu�une t�che ne peut pas entrer en production sur une machine avant que celle - ci ne soit libre :
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

	// Contrainte indiquant que chaque job doit passer dans chaque machine dans l�ordre :
	for (int i = 1; i < inst.m; i++) {
		for (int j = 0; j< inst.n; j++) {
			if (C[i][j] < C[i-1][j] + inst.p[i][j])
				return false;
		}
	}

	// Chaque commande doit �tre transport�e dans un v�hicule :
	for (int j = 0; j < inst.n; j++) {
		int sum = 0;
		for (int k = 0; k < inst.n; k++) {
			sum += (int) z[j][k];
		}
		if (sum != 1)
			return false;
	}

	// Chaque v�hicule ne peut partir que si les commandes qu�il doit transporter sont produites :
	for (int k = 0; k < inst.n; k++) {
		for (int j = 0; j < inst.n; j++) {
			if (F[k] < C[inst.m - 1][j] - HV * (1 - (double) z[j][k]))
				return false;
		}
	}

	// Une commande ne peut pas �tre livr�e tant qu�elle n�est pas produite :
	for (int j = 0; j < inst.n; j++) {
		for (int k = 0; k < inst.n; k++) {
			if (f[j] < F[k] - HV * (1 - (double)z[j][k]))
				return false;
		}
	}

	// Un v�hicule k est utilis� � partir du moment o� il doit transporter au moins une commande :
	for (int k = 0; k < inst.n; k++) {
		int sum = 0;
		for (int j = 0; j < inst.n; j++) {
			sum += (int)z[j][k];
		}
		if (HV * Z[k] < sum)
			return false;
	}

	// TODO Dans un m�me lot, un job j1 a un pr�d�cesseur j2 avec un seuil de livraison inf�rieur, sinon le
	// pr�d�cesseur est le site de production
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int k = 0; k < inst.n; k++) {

		}
	}
	// TODO

	//Pour le routage d�un v�hicule k, le site de production a un successeur seulement si le v�hicule k est utilis� :
	for (int k = 0; k < inst.n; k++) {
		int sum = 0;
		for (int j = 0; j < inst.n; j++) {
			sum += x[0][j][k];
		}
		if (sum > Z[k])
			return false;
	}

	// L�estimation de la date de livraison est donn�e via cette contrainte :
	for (int j1 = 0; j1 < inst.n; j1++) {
		for (int j2 = j1 + 1; j2 < inst.n; j2++) {
			for (int k = 0; k < inst.n; k++) {
				if (D_M[j2] < D_M[j1] + inst.t[j1 + 2][j2 + 2] - HV * (1 - (double)x[j1][j2][k]))
					return false;
			}
		}
	}

	// Contrainte donnant une borne inf�rieure sur la date de livraison d�une t�che j transport� par un v�hicule k :
	for (int j = 0; j < inst.n; j++) {
		for (int k = 0; k < inst.n; k++) {
			if (D_M[j] < F[k] + inst.t[0][j+2] - HV * (1 - (double)z[j][k]))
				return false;
		}
	}

	// Estimation du retard d�un job :
	for (int j = 0; j < inst.n; j++) {
		if (PT_M[j] < D_M[j] - inst.d[j])
			return false;
	}

	// Toutes les contraintes sont respect�es
	return true;
}
