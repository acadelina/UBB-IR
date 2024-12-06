#include"Serv.h"
#include<algorithm>

void Serv::adaugare(int id, string denum, string tip, int roti)
{
	Tractor t{ id,denum,tip,roti };
	repo.add(t);
}

void Serv::decrement(int id)
{
	int poz = -1;
	vector<Tractor> l = getAll();
	for (int i = 0; i < l.size(); i++)
		if (l[i].getid() == id)
			poz = i;
	repo.decRoti(poz);
}

vector<Tractor> Serv::getAll()
{
	return repo.getAll();
}

vector<Tractor> Serv::sort()
{
	vector<Tractor> l = getAll();
	std::sort(l.begin(), l.end(), [](Tractor& t1, Tractor& t2) {
		return t1.getdenum() < t2.getdenum();
		});
	return l;
}

map<string, int> Serv::sametip()
{
	map<string, int> m;
	for (auto e : getAll())
		m[e.gettip()]++;
	return m;
}

int Serv::roti(int poz)
{
	return getAll()[poz].getRoti();
}