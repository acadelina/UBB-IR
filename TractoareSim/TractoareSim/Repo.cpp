#include"Repo.h"
#include<sstream>

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
		while (getline(ss, a, ';'))
		{
			arg.push_back(a);
		}
		Tractor t{ stoi(arg[0]),arg[1],arg[2],stoi(arg[3]) };
		add(t);
	}

}

void Repo::save()
{
	ofstream fout(filename);
	vector<Tractor> tr = tractoare;
	for (auto& a : tr)
	{
		fout << a.getId() << ";" << a.getDenum() << ";" << a.getTip() << ";" << a.getRoti() << "\n";
	}
}

void Repo::add(Tractor& t)
{
	for (auto& a : tractoare)
	{
		if (a.getId() == t.getId())
			throw RepoException("Id deja existent");
	}
	tractoare.push_back(t);
}

vector<Tractor>& Repo::getAll()
{
	return this->tractoare;
}
