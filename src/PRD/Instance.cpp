#include "Instance.h"
#include <fstream>
#include <iostream>

using namespace std;


Instance::Instance()
{
	id = -1;
	n = 0;
	m = 0;
	p = vector<vector<int>>();
	d = vector<int>();
	t = vector<vector<int>>();
	h_WIP = vector<vector<int>>();
	h_FIN = vector<int>();
	p_M = vector<int>();
	c_V = 0;
}

Instance::Instance(string path)
{
    Parse(path);
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

	// Commandes
	for (int i = 0; i < n; i++) {
		int idCmd;
		file >> idCmd;
		if (idCmd != i) {
			file.close();
			throw exception("Format du fichier invalide");
			return false;
		}

		// Durées
		vector<int> p_row;
		for (int j = 0; j < m; j++) {
			int duree;
			file >> duree;
			p_row.push_back(duree);
		}
		p.push_back(p_row);

		// Cout d'inventaire WIP
		vector<int> h_WIP_row;
		h_WIP_row.push_back(0);
		for (int j = 0; j < m - 1; j++) {
			int cout;
			file >> cout;
			h_WIP_row.push_back(cout);
		}
		h_WIP.push_back(h_WIP_row);

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
		vector<int> row;
		for (unsigned int j = 0; j < coord.size(); j++) {
			row.push_back(sqrt(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2)));
		}
		t.push_back(row);
	}

	file.close();

    return true;
}
