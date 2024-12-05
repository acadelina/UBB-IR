#include"Melodie.h"
#include<cassert>

void testDomain()
{
	//Melodie m;
	Produs m2{1,"apa","bautura",5,"dorna"};
	assert(m2.getNume() == "apa");
	assert(m2.getTip() == "bautura");
	assert(m2.getProd() == "dorna");
	assert(m2.getPret() == 5);


}