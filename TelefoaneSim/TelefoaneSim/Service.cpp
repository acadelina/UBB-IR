#include "Service.h"
#include<algorithm>

vector<Telefon> Serv::filtm(string model)
{
	vector<Telefon> l = getL();
	vector<Telefon> filt;
	copy_if(l.begin(), l.end(), back_inserter( filt), [model](Telefon& t) {return t.getmodel() == model; });
	return filt;
}

vector<Telefon> Serv::filta(int an)
{
	vector<Telefon> l = getL();
	vector<Telefon> filt;
	copy_if(l.begin(), l.end(), back_inserter(filt), [an](Telefon& t) {return t.getan() == an; });
	return filt;
}

vector<Telefon> Serv::getL()
{
	return rep.getAll();
}

void testServ()
{
	Repo rep{ "test.txt" };
	Serv ser{ rep };
}