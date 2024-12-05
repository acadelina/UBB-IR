#include"Repo.h"
#include<sstream>
#include<cassert>
#include<fstream>

void Repo::load()
{
	ifstream fin(filename);
	string linie;
	while (getline(fin, linie))
	{
		if (linie.empty())
			continue;
		auto ss = stringstream(linie);
		vector<string> arg;
		string a;
		while (getline(ss, a, ','))
		{
			arg.push_back(a);
		}
		bool n;
		if (arg[4] == "True")
			n = true;
		else
			n = false;
		Rochie r { stoi(arg[0]),arg[1],arg[2],stoi(arg[3]),n};
		add(r);
	}
}

void Repo::save()
{
	vector<Rochie> r = getAll();
	ofstream fout(filename);
	for (auto a : r)
	{
		string disp;
		if (a.getdisp() == true)
			disp = "True";
		else
			disp = "False";
		fout << a.getcod() << "," << a.getdenum() << "," << a.getmarime() << "," << a.getpret() << "," <<disp<<"\n";
	}

}

void Repo::add(Rochie e)
{
	list.push_back(e);
	save();
}

vector<Rochie> Repo::getAll()
{
	return this->list;
}

void Repo::inchiriere(string d, string m, int p)
{
	vector<Rochie> r = getAll();
	Rochie e = cauta(d, m, p);
	for (auto a : r)
	{
		if (a.getcod() == e.getcod())
			a.setdisp(false);
	}
	save();
}

Rochie Repo::cauta(string d, string mar, int pret)
{
	vector<Rochie> r = getAll();
	for (auto a : r)
	{
		if (a.getdenum() == d && a.getmarime() == mar && a.getpret() == pret)
			return a;
	}
}

void testRepo()
{
	Repo rep{ "test.txt" };
	Rochie r=rep.cauta("r1", "s", 10);
	assert(r.getcod() == 1);
	assert(rep.getAll().size() == 5);
	rep.inchiriere("r1", "s", 10);

}