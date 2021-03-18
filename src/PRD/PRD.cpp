// PRD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "SolverControler.h"
#include "PSO.h"


/// <summary>
/// Point d'entrée du programme
/// </summary>
/// <returns></returns>
int main(int argc, char* argv[])
{
    string pathInstances;
    int nbPart;
    int duree;    

    cout << "\n//====================== PSO ======================\n\n";

    if (argc != 4) {
        // =================== PARAMETRES MANQUANTS ===================
        cout << "Erreur : le programme necessite 3 arguments : " << endl;
        cout << "- Dossier qui contient les instances " << endl;
        cout << "- Nombre de particules" << endl;
        cout << "- Duree maximum pour la resolution sur une instance" << endl;
    }
    else {
        pathInstances = argv[1];
        nbPart = atoi(argv[2]);
        duree = atoi(argv[3]);

        cout << "Voici les parametres : " << endl;
        cout << "- Dossier qui contient les instances : " << pathInstances << endl;
        cout << "- Nombre de particules : " << nbPart << endl;
        cout << "- Duree maximum pour la resolution sur une instance : " << duree << "s" << endl;
        cout << endl;

        PSO* pso = new PSO(duree, nbPart);
        SolverControler solverControl = SolverControler(pso);
        try {
            // =================== IMPORT ===================
            cout << "Import du dossier..." << endl;
            solverControl.ImportInstances(pathInstances);

            // =================== CALCUL ===================
            cout << "Running..." << endl;
            solverControl.LaunchComputation();

            // =================== EXPORT ===================
            cout << "Export des resultats..." << endl;
            string resName = "";
            resName = resName + "Resultat_PSO_" + to_string(nbPart) + "p_" + to_string(duree) + "s.txt";
            bool stay = true;
            // Vérifie si les résultats du même nom existe
            while (stay) {
                if (fileExist(resName)) {
                    resName = resName.substr(0, resName.size() - 4);
                    resName = resName + "(copie).txt";
                }
                else {
                    stay = false;
                }
            }
            solverControl.ExportResults(resName);
            cout << "SUCCES : les resultats sont disponibles dans le fichier suivant : " << resName << endl;
        }
        catch (exception &exc) {
            cout << "ERREUR : " << exc.what() << endl;
        }

        delete(pso);
    }

    cout << "\n//====================== PSO ======================\n\n";
    
}