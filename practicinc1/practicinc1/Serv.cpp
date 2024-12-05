#include"Serv.h"
#include<cassert>
vector<Melodie> Serv::getAll()
{
	return repo.getMel();
}

void Serv::modificR(int r, int id)
{
	
	int poz = repo.cauta(id);
	repo.schimbR(poz, r);
}


void Serv::modificT( int id,string t)
{
	int poz = repo.cauta(id);
	repo.schimbT(poz, t);
}

map<int,int> Serv::sameR()
{
	map<int, int> r;
	vector<Melodie> mel = getAll();
	for (auto e : mel)
	{
		r[e.getrank()]++;
	}
	return r;
}

void Serv::sterge(int id)
{
	int poz = repo.cauta(id);
	repo.del(poz);
}

void testServ()
{
	Repo rep{ "test.txt" };
	Serv serv{ rep };
	assert(serv.getAll().size() == 3);
	serv.modificR(5, 1);
	vector<Melodie> v = serv.getAll();
	assert(v[0].getrank() == 5);
	serv.sterge(1);
	assert(serv.getAll().size() == 2);

}