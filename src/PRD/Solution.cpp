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

    return nullptr;
}
