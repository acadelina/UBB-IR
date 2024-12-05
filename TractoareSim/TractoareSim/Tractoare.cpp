#include"Tractoare.h"
#include<cassert>
void testDomain()
{
	Tractor t{ 1,"tr1","tip1",4 };
	assert(t.getId() == 1);
	assert(t.getDenum() == "tr1");
	assert(t.getTip() == "tip1");
	assert(t.getRoti() == 4);
}