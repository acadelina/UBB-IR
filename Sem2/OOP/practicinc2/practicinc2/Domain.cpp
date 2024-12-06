#include"Domain.h"
#include<cassert>

void testDomain()
{
	Melodie m{ 1,"titlu1","art1","pop" };
	assert(m.getid() == 1);
	assert(m.gettitlul() == "titlu1");
	assert(m.getartist() == "art1");
	assert(m.getgen() == "pop");
}