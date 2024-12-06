#include"Domain.h"
#include<cassert>

void testDomain()
{
	Rochie r{ 1,"r1","s",10,true };
	assert(r.getcod() == 1);
	assert(r.getdenum() == "r1");
	assert(r.getmarime() == "s");
	assert(r.getpret() == 10);
	assert(r.getdisp() == true);

}