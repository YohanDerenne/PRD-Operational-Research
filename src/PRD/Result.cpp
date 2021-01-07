#include "Result.h"

Result::Result(Instance* instance)
{
	inst = new Instance(*instance);
	cout_total = 0;
	cout_WIP = 0;
	cout_FIN = 0;
	cout_retard = 0;
}

Result::Result(const Result& res2)
{
	inst = new Instance(*res2.inst);
	cout_total = res2.cout_total;
	cout_WIP = res2.cout_WIP;
	cout_FIN = res2.cout_FIN;
	cout_retard = res2.cout_retard;
}

Result::~Result()
{
	if (inst != NULL) {
		delete inst;
	}
}
