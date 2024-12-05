#include"Domain.h"
#include<cassert>

void testDomain()
{
	Tractor t{ 1,"t1","tip1",4 };
	assert(t.getid() == 1);
	assert(t.getdenum() == "t1");
	assert(t.gettip() == "tip1");
	assert(t.getRoti() == 4);
}