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
        double mini = 999999999;
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
  
    idle = sv3;

    // Dates de fin des jobs
    vector<vector<double>> a(inst->m, std::vector<double>(inst->n, 0));
    res->C[0][ordre[0]] = idle[0][ordre[0]] + inst->p[0][ordre[0]];
    for (int k = 1; k < inst->m; k++) {
        res->C[k][ordre[0]] = res->C[k-1][ordre[0]] + idle[k][ordre[0]] + inst->p[k][ordre[0]];
    }
    for (int i = 1; i < inst->m; i++) {
        res->C[0][ordre[i]] = res->C[0][ordre[i-1]] + idle[0][ordre[i]] + inst->p[0][ordre[i]];
    }
    for (int i = 1; i < inst->m; i++) {
        for (int k = 1; k < inst->n; k++) {
            res->C[k][ordre[i]] = max(res->C[k - 1][ordre[i]] + idle[k][ordre[i]] + inst->p[k][ordre[i]],
                res->C[k][ordre[i-1]] + idle[k][ordre[i]] + inst->p[k][ordre[i]]);
        }
    }

    return res;
}
