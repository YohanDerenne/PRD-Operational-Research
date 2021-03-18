#include "Instance.h"
#include <fstream>
#include <iostream>

using namespace std;


Instance::Instance()
{
	id = -1;
	n = 0;
	m = 0;
	p = vector<vector<double>>();
	d = vector<int>();
	t = vector<vector<double>>();
	h_WIP = vector<vector<int>>();
	h_FIN = vector<int>();
	p_M = vector<int>();
	c_V = 0;
}

Instance::Instance(string path)
{
	try {
		Parse(path);
	}
	catch (exception &ex) {
		throw ex;
	}
}

Instance::Instance(const Instance& inst2)
{
	id = inst2.id;
	n = inst2.n;
	m = inst2.m;
	p = inst2.p;
	d = inst2.d;
	t = inst2.t;
	h_WIP = inst2.h_WIP;
	h_FIN = inst2.h_FIN;
	p_M = inst2.p_M;
	c_V = inst2.c_V;
}

bool Instance::Parse(string path)
{
	ifstream file;
	file.open(path);
	if (!file) {
		throw invalid_argument("Impossible d'ouvrir le fichier en lecture");
		return false;
	}

	// Nb cmd - Nb machines - cout vehicule - index
	file >> n >> m >> c_V >> id;

	// Coordonnées
	vector<pair<int, int>> coord;


	p = vector<vector<double>>(m, vector<double>(n, 0));
	h_WIP = vector<vector<int>>(m, vector<int>(n, 0));

	// Commandes
	for (int j = 0; j < n; j++) {
		int idCmd;
		file >> idCmd;
		if (idCmd != j) {
			file.close();
			string msg = "ERREUR : Format du fichier invalide dans le fichier " + path + (". Il se peut que le problème soit avant le traitement de la commande #" + j);
			throw exception(msg.c_str());
			return false;
		}

		// Durées
		//vector<double> p_row;
		for (int i = 0; i < m; i++) {
			double duree;
			file >> duree;
			p[i][j] = duree;
		}
		//p.push_back(p_row);

		// Cout d'inventaire WIP
		//vector<int> h_WIP_row;
		h_WIP[0][j] = 0;
		for (int i = 1; i < m; i++) {
			int cout;
			file >> cout;
			h_WIP[i][j] = cout;
			//h_WIP_row.push_back(cout);
		}
		//h_WIP.push_back(h_WIP_row);

		// Cout d'inventaire FIN
		int cout_FIN;
		file >> cout_FIN;
		h_FIN.push_back(cout_FIN);

		// Date livraison souhaitée
		int date;
		file >> date;
		d.push_back(date);

		// Penalite retard
		int penalty;
		file >> penalty;
		p_M.push_back(penalty);

		// Autre penalite
		file >> penalty;

		// Destination cmd
		int x_dest;
		int y_dest;
		file >> x_dest >> y_dest;
		coord.push_back({ x_dest, y_dest });
	}

	// Coord prod
	int x_prod;
	int y_prod;
	file >> x_prod >> y_prod;

	// Coord distrib
	int x_distrib;
	int y_distrib;
	file >> x_distrib >> y_distrib;

	coord.insert(coord.begin(), { x_distrib ,y_distrib });
	coord.insert(coord.begin(), { x_prod ,y_prod });

	// Calcul Distances 
	for (unsigned int i = 0; i < coord.size(); i++) {
		vector<double> row;
		for (unsigned int j = 0; j < coord.size(); j++) {
			row.push_back(sqrt(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2)));
		}
		t.push_back(row);
	}

	file.close();

    return true;
}
