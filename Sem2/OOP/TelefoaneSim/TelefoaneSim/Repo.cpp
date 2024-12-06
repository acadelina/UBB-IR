#include"Repo.h"
#include<fstream>
#include<cassert>
#include<sstream>

void Repo::load()
{
	ifstream fin(filename);
	string line;
	while (getline(fin, line))
	{
		auto ss=stringstream(line);
		vector<string> arg;
		string a;
		while (getline(ss, a, ';'))
		{
			arg.push_back(a);
		}
		Telefon t{ arg[0],arg[1],arg[2],stoi(arg[3]),stoi(arg[4]) };
		add(t);
	}
}

void Repo::save()
{
	vector<Telefon> t = tel;
	ofstream out(filename);
	for (auto a : t)
	{
		out << a.gettip() << ";" << a.getmodel() << ";" << a.getculoare() << ";" << a.getan() << ";" << a.getpret() << "\n";
	}
}

void Repo::add(Telefon& t)
{
	tel.push_back(t);
}

vector<Telefon> Repo::getAll()
{
	return this->tel;
}

void testRepo()
{
	Repo rep = Repo{ "test.txt" };
	vector<Telefon> l = rep.getAll();
	assert(int(l.size()) == 2);
	assert(l[0].gettip() == "samsung");
	assert(l[0].getmodel() == "galaxy");
	assert(l[0].getculoare() == "alb");
	assert(l[0] .getan() == 2020);
	assert(l[0].getpret() == 1100);
}