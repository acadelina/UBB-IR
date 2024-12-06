#include"Domain.h"
#include<cassert>
void testDomain()
{
	Produs p{ 1,"p1","t1",3 };
	assert(p.getid() == 1);
	assert(p.getnume() == "p1");
	assert(p.gettip() == "t1");
	assert(p.getpret() == 3);
}