#include "disciplina.h"
#include<cassert>

void testDomain()
{
	Disciplina d{ "info",4,"t1","prof1" };
	assert(d.getDenum() == "info");
	assert(d.getOre() == 4);
	assert(d.getProf() == "prof1");
	assert(d.getTip() == "t1");
}