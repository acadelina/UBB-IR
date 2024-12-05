#include"Serv.h"
#include<algorithm>
#include<cassert>

void Serv::modificare(int id, string titlu, int rank)
{
	rep.modif(id, titlu, rank);
}

void Serv::sterge(int id)
{
	
	int poz = rep.cauta(id);
	if (art(rep.getAll()[poz].getartist()) <= 1)
		throw exception("Artistul nu mai are melodii");
	rep.del(id);
}

vector<Melodie> Serv::sort()
{
	vector<Melodie> m = rep.getAll();
	std::sort(m.begin(), m.end(), [](Melodie& m1, Melodie& m2) {
		return m1.getrank() < m2.getrank();
		});
	return m;
}

map<int, int> Serv::rankuri()
{
	map<int, int> m;
	for (auto e : rep.getAll())
		m[e.getrank()]++;
	return m;
}

int Serv::art(string a)
{
	int nr = 0;
	for (auto e : rep.getAll())
		if (e.getartist() == a)
			nr++;
	return nr;
}

void testServ()
{
	Repo rep{ "test.txt" };
	Serv serv{ rep };
	assert(serv.sort().size() == 2);
	vector<Melodie> v = serv.sort();
	assert(v[0].getid() == 4);
	assert(v[1].getid() == 5);
	serv.modificare(4, "nou", 2);
	v = serv.sort();
	assert(v[0].gettitlu() == "nou");
	assert(v[0].getrank() == 2);
	try {
		serv.sterge(4);
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}
	//assert(serv.sort().size() == 1);

}