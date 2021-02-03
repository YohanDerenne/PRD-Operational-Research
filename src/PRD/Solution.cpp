#include "Solution.h"
#include <algorithm>

Result* Solution::Decode(Instance* inst)
{
    Result* res = new Result(inst);
    int HV = 999999999;

    // SPV Rule
    vector<double> tmpSv1 = sv1;
    ordre.clear();
    for (int k = 0; k < sv1.size(); k++) {
        ordre.push_back(0);
    }
    for (int pos = 0 ; pos < inst->n; pos++) {
        double mini = HV;
        int index = -1;
        for (int i = 0; i < sv1.size(); i++) {
            if (mini > tmpSv1[i]) {
                mini = tmpSv1[i];
                index = i;
            }
        }
        ordre[index] = pos;
        tmpSv1[index] = HV;
    }

    // NDVR - affectation vehicule
    for (int i = 0; i < sv2.size(); i++) {
        affectV.push_back(round(sv2[i])); //TODO - arrondi ok?
    }
    res->V = *std::max_element(affectV.begin(), affectV.end()) + 1; // nb V
    res->z = vector<vector<bool>>(inst->n, vector<bool>(inst->n, false));
    for (int j = 0; j < inst->n; j++) {
        for (int k = 0; k < res->V; k++) {
            if (affectV[j] == k) {
                res->z[j][k] = true;
            }
            else {
                res->z[j][k] = false;
            }
        }
    }
  
    // sv3 no predecode
    idle = sv3;

    // Dates de fin des jobs
    res->C = vector<vector<double>>(inst->m, vector<double>(inst->n, -1));    //TODO [I][J] = [machine][Job] ou [Job][Machine]?
    res->C[0][ordre[0]] = idle[0][ordre[0]] + inst->p[0][ordre[0]];
    for (int k = 1; k < inst->n; k++) {
        res->C[0][ordre[k]] = res->C[0][ordre[k - 1]] + idle[0][ordre[k]] + inst->p[0][ordre[k]];
    }
    for (int i = 1; i < inst->m; i++) {
        res->C[i][ordre[0]] = res->C[i-1][ordre[0]] + idle[i][ordre[0]] + inst->p[i][ordre[0]];
    }
    for (int i = 1; i < inst->m; i++) {
        for (int k = 1; k < inst->n; k++) {
            res->C[i][ordre[k]] = max(res->C[i][ordre[k - 1]] + idle[i][ordre[k]] + inst->p[i][ordre[k]],
                res->C[i-1][ordre[k]] + idle[i][ordre[k]] + inst->p[i][ordre[k]]);
        }
    }

    // Dates de départ des véhicules    
    res->F = vector<double>(res->V, -1);
    for (int k = 0; k < res->V ; k++) {
        vector<double> jobAffected;
        for (int j = 0; j < inst->n; j++) {
            if (affectV[j] == k) {
                jobAffected.push_back(res->C[inst->m - 1][j]);
            }
        }
        res->F[k] = *max_element(jobAffected.begin(), jobAffected.end());
    }

    // Dates de départ des taches
    res->f = vector<double>(inst->n, -1);
    for (int i = 0; i < inst->n; i++) {
        res->f[i] = res->F[affectV[i]];
    }

    // Calcul couts
    res->IC_WIP = 0;
    res->IC_FIN = 0;
    for (int j = 0; j < inst->n; j++) {
        for (int i = 0; i < inst->m - 1; i++) {
            res->IC_WIP += (res->C[i + 1][j] - inst->p[i + 1][j] - res->C[i][j]) * inst->h_WIP[i][j];
        }
    }
    for (int j = 0; j < inst->n; j++) {
        res->IC_FIN = (res->f[j] - res->C[inst->m-1][j]) * inst->h_FIN[j];
    }
    res->IC = res->IC_WIP + res->IC_FIN;

    //Dates de livraison    
    vector<int> lieuDesservi;
    res->D_M = vector<double>(inst->n, -1);
    for (int k = 0; k < res->V; k++) {
        int lieu = 0; // depot
        double dateCourante = res->F[k];

        for (int i = 0; i < inst->n; i++) {
            //PPV
            int lieuPlusProche = -1;
            int distMini = HV;
            for (int l = 0; l < inst->n; l++) {
                if (res->z[i][k] == false) { // transporté par k
                    continue;
                }
                if (distMini > inst->t[lieu][l] && count(lieuDesservi.begin(), lieuDesservi.end(), l) == 0) { // Dist mini && non desservie
                    lieuPlusProche = l;
                    distMini = inst->t[lieu][l];
                }
            }
            if (lieuPlusProche == -1)
                continue;

            lieuDesservi.push_back(lieuPlusProche);
            res->D_M[lieuPlusProche] = dateCourante + inst->t[lieu][lieuPlusProche]; //TODO D manu ou 3pl?
            dateCourante += inst->t[lieu][lieuPlusProche];
            lieu = lieuPlusProche; // maj lieu   
        }            
    }

    return res;
}
