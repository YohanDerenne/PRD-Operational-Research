#include "Solution.h"

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

    // NDVR
    for (int i = 0; i < sv2.size(); i++) {
        affectV.push_back(round(sv2[i]));
    }
  
    // No decode
    idle = sv3;
    idle = vector<vector<double>>(inst->n, vector<double>(inst->m, 0.0));

    // Dates de fin des jobs
    res->C = vector<vector<double>>(inst->n, vector<double>(inst->m, 0.0));    
    res->C[ordre[0]][0] = idle[ordre[0]][0] + inst->p[ordre[0]][0];
    for (int k = 1; k < inst->n; k++) {
        res->C[ordre[k]][0] = res->C[ordre[k-1]][0] + idle[ordre[k]][0] + inst->p[ordre[k]][0];
    }
    for (int i = 1; i < inst->m; i++) {
        res->C[ordre[0]][i] = res->C[ordre[0]][i-1] + idle[ordre[0]][i] + inst->p[ordre[0]][i];
    }
    for (int i = 1; i < inst->m; i++) {
        for (int k = 1; k < inst->n; k++) {
            res->C[ordre[k]][i] = max(res->C[ordre[k-1]][i] + idle[ordre[k]][i] + inst->p[ordre[k]][i],
                res->C[ordre[k]][i-1] + idle[ordre[k]][i] + inst->p[ordre[k]][i]);
        }
    }

    return res;
}
