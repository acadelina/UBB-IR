#include"Repo.h"
#include<fstream>
#include<sstream>
#include<cassert>
using namespace std;

void Repo::load()
{
	ifstream f(filename);
	string linie;
	while (getline(f, linie))
	{
		auto ss = stringstream(linie);
		string cuv;
		vector<string> arg;
		while (getline(ss, cuv, ','))
		{
			arg.push_back(cuv);
		}
		Produs p{ stoi(arg[0]),arg[1],arg[2],stod(arg[3]) };
		v.push_back(p);
	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : v)
	{
		g << e.getid() << "," << e.getnume() << "," << e.gettip() << "," << e.getpret() << "\n";
	}
}

void Repo::add(Produs& p)
{
	string msg = "";
	if (p.getnume() == "")
		msg += "Nume invalid\n";
	if (p.getpret() < 1 || p.getpret() > 100)
		msg += "Pret invalid\n";
	for (auto e : v)
	{
		if (e.getid() == p.getid())
		{
			msg += "Id invalid\n";
			break;
		}
	}
	if (msg != "")
		throw RepoExc(msg);
	v.push_back(p);
	save();
}

vector<Produs> Repo:: getAll()
{
	return v;
}

void testRepo()
{
	Repo rep{ "test.txt" };
	assert(rep.getAll().size() == 0);
	Produs p1{ 1,"p1","t1",5 };
	Produs p2{ 2,"p2","t1",10 };
	rep.add(p1);
	rep.add(p2);
	assert(rep.getAll().size() == 2);

}