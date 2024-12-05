#include"Serv.h"
#include<algorithm>

vector<Melodie> Serv::getAll()
{
	return rep.getMel();
}

vector<Melodie> Serv::sort()
{
	vector<Melodie> m = rep.getMel();
	std::sort(m.begin(), m.end(), [](Melodie& m1, Melodie& m2) {
		return m1.getartist() > m2.getartist();
		});
	return m;
}

void Serv::adauga(int id, string t, string a, string g)
{
	Melodie m{ id,t,a,g };
	rep.add(m);
}

void Serv::stergere(int id)
{
	int poz = rep.cauta(id);
	rep.sterge(poz);
}

map<string, int> Serv::sameA()
{
	map<string, int> d;
	for (auto& e : getAll())
	{
		d[e.getartist()]++;
	}
	return d;
}

map<string, int> Serv::sameG()
{
	map<string, int> d;
	for (auto& e : getAll())
	{
		d[e.getgen()]++;
	}
	return d;
}

