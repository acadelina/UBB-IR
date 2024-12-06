#include"Repo.h"
#include<sstream>
#include<fstream>

void Repo::load()
{
	ifstream f(filename);
	string linie;
	while (getline(f, linie))
	{
		
		vector<string> arg;
		string cuv;
		auto ss = stringstream(linie);
		while (getline(ss, cuv, ','))
		{
			arg.push_back(cuv);
		}
		Produs p{ stoi(arg[0]),arg[1],arg[2],stod(arg[3]) };
		add(p);



	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : produse)
		g << e.getid() << ',' << e.getnume() << "," << e.gettip() << "," << e.getpret() << "\n";
}

void Repo::add(Produs& p)
{
	for (auto e : produse)
		if (e.getid() == p.getid())
			throw RepoError("Id existent\n");
	produse.push_back(p);
	save();
}

vector<Produs> Repo::getAll()
{
	return produse;
}