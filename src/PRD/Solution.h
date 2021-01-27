#pragma once

#include "Result.h"

class Solution
{
public :
	vector<double> sv1;
	vector<double> sv2;
	vector<vector<double>> sv3;

	vector<int> ordre;
	vector<int> affectV;
	vector<vector<double>> idle;

	Result* Decode(Instance * inst);
};

