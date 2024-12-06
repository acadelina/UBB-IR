#include"Domain.h"
#include<cassert>

void testDomain()
{
	Task t{ 1,"desc",{"ana","maria"},"open" };
	assert(t.getid() == 1);
	assert(t.getdesc() == "desc");
	assert(t.getprog().size() == 2);
	assert(t.getstare() == "open");
}