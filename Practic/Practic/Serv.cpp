#include"Serv.h"
#include<algorithm>
#include<cassert>
using namespace std;

void Serv::adaugare(int id, string desc, string stare, vector<string> p)
{
	Task t{ id,desc,stare,p };
	rep.add(t);
	notify();
}

vector<Task> Serv::getAll()
{
	vector<Task> v = rep.getT();
	std::sort(v.begin(), v.end(), [](Task& t1, Task& t2) {
		return t1.getstare() < t2.getstare();
		});
	return v;
}

vector<Task> Serv::filtr(string p)
{
	vector<Task> t;
	for (auto a : rep.getT())
	{
		if (rep.searchP(a, p))
			t.push_back(a);
	}
	return t;
}

vector<Task> Serv::stari(string stare)
{
	vector<Task> t;
	for (auto a : rep.getT())
	{
		if (a.getstare() == stare)
			t.push_back(a);
	}
	return t;
}

void Serv::modifica(int id, string stare)
{
	rep.schimbStare(id, stare);
	notify();
}

void testServ()
{
	Repo rep{ "test.txt" };
	Serv serv{ rep };
	assert(serv.getAll().size() == 5);
	assert(serv.filtr("p").size() == 1);
	assert(serv.stari("closed").size() == 0);
	serv.adaugare(16, "a", "open", { "p","p2" });
	assert(serv.getAll().size() == 6);
	serv.modifica(16, "closed");
	assert(serv.stari("closed").size() == 1);

}