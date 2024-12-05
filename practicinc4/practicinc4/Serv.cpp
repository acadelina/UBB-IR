#include"Serv.h"
#include<algorithm>
using namespace std;

void Serv::adaugare(int id, string d, vector<string > p, string st)
{
	Task t{ id, d, p, st };
	rep.add(t);
	notify();
}

vector<Task> Serv::getAll()
{
	return rep.getT();
}

vector<Task> Serv::sort()
{
	vector<Task> rez = getAll();
	std::sort(rez.begin(), rez.end(), [](Task& t1, Task& t2) {
		return t1.getstare() > t2.getstare();
		});
	return rez;
}

vector<Task> Serv::search(string p)
{
	vector<Task> rez = getAll();
	vector<Task> l;
	for (auto a : rez)
	{
		if (rep.cauta(a, p))
			l.push_back(a);
	}
	return l;
}

map<string, vector<Task>> Serv::stari()
{
	map<string, vector<Task>> m;
	for (auto e : getAll())
	{
		m[e.getstare()].push_back(e);
	}
	return m;
}

void Serv::schimbs(int id, string n)
{
	int poz = -1;
	int i = 0;
	for (auto a : getAll())
	{
		if (a.getid() == id)
			poz = i;
		i++;
	}
	rep.change(poz, n);
	notify();
}
