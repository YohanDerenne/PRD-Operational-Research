#include "Solution.h"
#include <algorithm>
#include <cassert>

Solution::Solution(Instance instance) : resultatDecode(instance)
{
    inst = instance;
}


Result Solution::Decode()
{
    resultatDecode = Result(inst);
    double HV = DBL_MAX;

    // SPV Rule
    vector<double> tmpSv1 = sv1;
    ordre.clear();
    for (int k = 0; k < sv1.size(); k++) {
        ordre.push_back(0);
    }
    for (int pos = 0 ; pos < inst.n; pos++) {
        double mini = HV;
        int index = -1;
        for (int i = 0; i < sv1.size(); i++) {
            if (mini > tmpSv1[i]) {
                mini = tmpSv1[i];
                index = i;
            }
        }
        if (index == -1)
            assert(!"Impossible");
        ordre[pos] = index;
        tmpSv1[index] = HV;
    }

    // NDVR - affectation vehicule
    affectV.clear();
    for (int i = 0; i < sv2.size(); i++) {
        double rand = round(sv2[i]);
        if (rand < 0)
            rand = 0;
        if (rand > (inst.n - 1.0))
            rand = inst.n - 1.0;
        affectV.push_back(rand); //TODO - arrondi ok?
    }
   
    resultatDecode.z = vector<vector<bool>>(inst.n, vector<bool>(inst.n, false));
    for (int j = 0; j < inst.n; j++) {
        for (int k = 0; k < inst.n ; k++) {
            if (affectV[j] == k) {
                resultatDecode.z[j][k] = true;
            }
            else {
                resultatDecode.z[j][k] = false;
            }
        }
    }
    
  
    // sv3 no predecode
    idle = sv3;

    // Dates de fin des jobs
    resultatDecode.C = vector<vector<double>>(inst.m, vector<double>(inst.n, -1));    //TODO [I][J] = [machine][Job] ou [Job][Machine]?
    resultatDecode.C[0][ordre[0]] = idle[0][ordre[0]] + inst.p[0][ordre[0]];
    for (int k = 1; k < inst.n; k++) {
        resultatDecode.C[0][ordre[k]] = resultatDecode.C[0][ordre[k - 1]] + idle[0][ordre[k]] + inst.p[0][ordre[k]];
    }
    for (int i = 1; i < inst.m; i++) {
        resultatDecode.C[i][ordre[0]] = resultatDecode.C[i-1][ordre[0]] + idle[i][ordre[0]] + inst.p[i][ordre[0]];
    }
    for (int i = 1; i < inst.m; i++) {
        for (int k = 1; k < inst.n; k++) {
            resultatDecode.C[i][ordre[k]] = max(resultatDecode.C[i][ordre[k - 1]] + idle[i][ordre[k]] + inst.p[i][ordre[k]],
                resultatDecode.C[i-1][ordre[k]] + idle[i][ordre[k]] + inst.p[i][ordre[k]]);
        }
    }

    // Dates de départ des véhicules    
    resultatDecode.F = vector<double>(inst.n, -1);
    resultatDecode.Z = vector<bool>(inst.n, false);
    for (int k = 0; k < resultatDecode.inst.n ; k++) {
        vector<double> jobAffected;
        for (int j = 0; j < inst.n; j++) {
            if (affectV[j] == k) {
                jobAffected.push_back(resultatDecode.C[inst.m - 1][j]);
            }
        }
        if (jobAffected.size() > 0) {
            resultatDecode.F[k] = *max_element(jobAffected.begin(), jobAffected.end());
            resultatDecode.Z[k] = true; // vehicule utilisé
        }        
    }
    resultatDecode.V = std::count(resultatDecode.Z.begin(), resultatDecode.Z.end(), true); // nb V

    // Dates de départ des taches
    resultatDecode.f = vector<double>(inst.n, -1);
    for (int i = 0; i < inst.n; i++) {
        resultatDecode.f[i] = resultatDecode.F[affectV[i]];
    }

    // Calcul couts
    resultatDecode.IC_WIP = 0;
    resultatDecode.IC_FIN = 0;
    for (int j = 0; j < inst.n; j++) {
        for (int i = 0; i < inst.m - 1; i++) {
            resultatDecode.IC_WIP += (resultatDecode.C[i + 1][j] - inst.p[i + 1][j] - resultatDecode.C[i][j]) * inst.h_WIP[i+1][j];
        }
    }
    for (int j = 0; j < inst.n; j++) {
        resultatDecode.IC_FIN = (resultatDecode.f[j] - resultatDecode.C[inst.m-1][j]) * inst.h_FIN[j];
    }
    resultatDecode.IC = resultatDecode.IC_WIP + resultatDecode.IC_FIN;
    resultatDecode.VC = inst.c_V * resultatDecode.V;

    //Dates de livraison    
    vector<int> lieuDesservi;
    resultatDecode.D_M = vector<double>(inst.n, -1);
    for (int k = 0; k < resultatDecode.inst.n; k++) {
        int lieu = 0; // 0 = depot prod , 1 = depot distrib, autresultatDecode = lieu de livraison des cmd
        double dateCourante = resultatDecode.F[k];

        for (int i = 0; i < inst.n; i++) {
            if (resultatDecode.z[i][k] == false) { // pas transporté par k
                continue;
            }

            //PPV
            int lieuPlusProche = -1;
            int distMini = INT_MAX;

            for (int l = 2; l < inst.n + 2; l++) { // à partir de 2 car avant on a les depot prod et distri
                if (resultatDecode.z[l-2][k] == false) { // pas transporté par k
                    continue;
                }
                
                if (distMini > inst.t[lieu][l] && count(lieuDesservi.begin(), lieuDesservi.end(), l) == 0) { // Dist mini && non desservie
                    lieuPlusProche = l;
                    distMini = inst.t[lieu][l];
                }
            }
            if (lieuPlusProche == -1)
                continue;

            lieuDesservi.push_back(lieuPlusProche);
            resultatDecode.D_M[lieuPlusProche-2] = dateCourante + inst.t[lieu][lieuPlusProche]; //TODO D manu ou 3pl?
            dateCourante += inst.t[lieu][lieuPlusProche];
            lieu = lieuPlusProche; // maj lieu   
        }            
    }

    // y et x pour l'ordonnancement 
    resultatDecode.y = vector<vector<bool>>(inst.n, vector<bool>(inst.n, false));
    resultatDecode.x = vector<vector<vector<bool>>>(inst.n,vector<vector<bool>>(inst.n, vector<bool>(inst.n, false)));
    for (int i = 0; i < inst.n; i++) {
        for (int j = 0; j < inst.n; j++) {
            int id1;
            int id2;
            for (int k = 0; k < inst.n; k++) {
                if (ordre[k] == i)
                    id1 = k;
                if (ordre[k] == j)
                    id2 = k;
            }
            if (id1 < id2) 
                resultatDecode.y[i][j] = true;
            else
                resultatDecode.y[i][j] = false;

            if (affectV[i] == affectV[j] && resultatDecode.D_M[i] < resultatDecode.D_M[j]) // TODO D_M ou D_3PL
                resultatDecode.x[i][j][affectV[i]] = true;            
        }
    }

    // retard
    resultatDecode.PT_M = vector<double>(inst.n, 0);
    resultatDecode.PPC_M = 0;
    for (int j = 0; j < inst.n; j++) {
        resultatDecode.PT_M[j] = max(0.0, resultatDecode.D_M[j] - inst.d[j]); // TODO D_M D_3PL
        resultatDecode.PPC_M += inst.p_M[j] * resultatDecode.PT_M[j];
    }


    // Cout total
    resultatDecode.cout_total = resultatDecode.PPC_M + resultatDecode.IC + resultatDecode.VC;

    return resultatDecode;
}

