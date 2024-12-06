#include"Domain.h"
#include<cassert>

void testDomain()
{
	Joc j{ 1,3,"X-OXO-XOO","X","Terminat" };
	assert(j.getid() == 1);
	assert(j.getdim() == 3);
	assert(j.gettabla() == "X-OXO-XOO");
	assert(j.getjuc() == "X");
	assert(j.getstare() == "Terminat");

}