#include"Domain.h"
#include<cassert>

void testDomain()
{
	Task t{ 1,"des","open",{"p1","p2"} };
	assert(t.getid() == 1);
	assert(t.getdesc() == "des");
	assert(t.getprog().size() == 2);
	assert(t.getstare() == "open");

}