#include"Serv.h"
#include"Validator.h"
#include<algorithm>

vector<Produs> Serv::getP()
{
	return rep.getAll();
}

vector<Produs> Serv::sortP()
{
	vector<Produs> rez = getP();
	std::sort(rez.begin(), rez.end(), [](Produs& p1, Produs& p2) {
		return p1.getpret() > p2.getpret();
		});
	return rez;
}

vector<Produs> Serv::filtr(int pret)
{
	vector<Produs> rez;
	for (auto e : getP())
	{
		if (e.getpret() <= pret)
			rez.push_back(e);
	}
	return rez;
}
map<string, int> Serv::tipuri()
{
	map<string, int> t;
	for (auto e : getP())
	{
		t[e.gettip()]++;
	}
	return t;
}

void Serv::adauga(int id, string nume, string tip, double pret)
{
	Produs p{ id,nume,tip,pret };
	val.validare(nume, pret);
	rep.add(p);
	notify();
}