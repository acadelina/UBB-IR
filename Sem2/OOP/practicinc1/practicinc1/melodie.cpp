#include"melodie.h"
#include<cassert>

void testDomain()
{
	Melodie m{ 0,"","",0};
	m.setid(1);
	m.settitlu("Titlu");
	m.setartist("Artist");
	m.setrank(3);
	assert(m.getid() == 1);
	assert(m.getartist() == "Artist");
	assert(m.getrank() == 3);
	assert(m.gettitlu() == "Titlu");
}