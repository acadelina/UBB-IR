#include"Domain.h"
#include<cassert>

void testDomain()
{
	Telefon t{ "samsung","galaxy","alb",2020,1100 };
	assert(t.gettip() == "samsung");
	assert(t.getmodel() == "galaxy");
	assert(t.getculoare() == "alb");
	assert(t.getan() == 2020);
	assert(t.getpret() == 1100);
}