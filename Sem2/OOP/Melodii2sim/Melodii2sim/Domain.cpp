#include"Domain.h"
#include<cassert>

void testDomain()
{
	Melodie m{ 1,"m1","a1","pop" };
	assert(m.getid() == 1);
	assert(m.gettitlu() == "m1");
	assert(m.getartist() == "a1");
	assert(m.getgen() == "pop");
}