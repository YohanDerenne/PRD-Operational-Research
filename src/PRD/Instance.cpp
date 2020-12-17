#include "Instance.h"
#include <fstream>
#include <iostream>

using namespace std;


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
	file >> n >> m >> c_V >> id;
	file.close();

    return true;
}
