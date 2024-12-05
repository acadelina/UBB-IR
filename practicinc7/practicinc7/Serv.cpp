#include"Serv.h"
#include<algorithm>

void Serv::adauga(int id, string nume, string tip, double pret)
{
	Produs p{ id,nume,tip,pret };
	rep.add(p);
	notify();
}

vector<Produs> Serv::sort()
{
	vector<Produs> p = rep.getAll();
	std::sort(p.begin(), p.end(), [](Produs& p1, Produs& p2) {
		return p1.getpret() < p2.getpret();
		});
	return p;
}

map<string, int> Serv::tipuri()
{
	map<string, int> m;
	for (auto e : rep.getAll())
		m[e.gettip()]++;
	return m;
}

void testServ()
{
	Repo rep{ "test.txt" };
	Serv serv{ rep };
	vector<Produs> v = serv.sort();
	assert(v[0].getid() == 1);
	assert(v[1].getid() == 2);
	map<string, int> m = serv.tipuri();
	assert(m.size() == 1);
	assert(m["t1"] == 2);
	serv.adauga(3, "p3", "t2", 10);
	assert(serv.sort().size() == 3);
}