#include "Instance.h"
#include <fstream>

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
		printf("ERREUR : Impossible d'ouvrir le fichier en lecture\n");
		return false;
	}
	file >> n >> m >> c_V >> id;
	file.close();

    return true;
}
