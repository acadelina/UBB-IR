#include"Domain.h"
#include<cassert>

void testDomain()
{
	Task t{ 1,"asas",{"ana","george","mihai"},"open" };
	assert(t.getid() == 1);
	assert(t.getdesc() == "asas");
	assert(t.getprog().size() == 3);
	assert(t.getstare() == "open");
}