#include"Serv.h"
#include<algorithm>

void Serv::adaugare(int id, string desc, vector<string> p, string stare)
{
	Task t{ id,desc,p,stare };
	rep.add(t);
	notify();
}

void Serv::modificare(int id, string stare)
{
	int poz = rep.cauta(id);
	rep.changes(poz, stare);
	notify();
}

vector<Task> Serv::sort()
{
	vector<Task> t = rep.getAll();
	std::sort(t.begin(), t.end(), [](Task& t1, Task& t2) {
		return t1.getstare() < t2.getstare();
		});
	return t;

}

vector<Task> Serv::stari(string stare)
{
	vector<Task> s;
	for (auto a : rep.getAll())
		if (a.getstare() == stare)
			s.push_back(a);
	return s;
}

vector<Task> Serv::filtrare(string prog)
{
	vector<Task> f;
	for (auto a : rep.getAll())
	{
		if (rep.search(prog, a))
			f.push_back(a);
	}
	return f;
}