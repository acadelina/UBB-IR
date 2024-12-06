#include "contract.h"
#include<cassert>

Contract::Contract()
{
}

void testContract()
{

	Disciplina d = { "info",10,"t1","Prof" };
	Contract cont;
	cont.addCont(d);
	vector<Disciplina> v = cont.getAllCont();
	assert(v.size() == 1);
	cont.clearContract();
	assert(cont.getAllCont().size() == 0);
	cont.fillContract(1, v);
	assert(cont.getAllCont().size() == 1);
	cont.clearContract();
	assert(cont.getAllCont().size() == 0);
	cont.fillContract(2, v);
	assert(cont.getAllCont().size() == 2);
	

}