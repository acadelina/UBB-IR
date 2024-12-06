#include"Repo.h"
#include<fstream>
#include<sstream>

void Repo::load()
{
	ifstream f(filename);

	string line;
	while (getline(f, line))
	{
		if (line.empty())
			continue;
		auto ss = stringstream(line);
		vector<string> arg;
		string a;
		while (getline(ss, a, ','))
		{
			arg.push_back(a);
		}
		Melodie m{ stoi(arg[0]),arg[1],arg[2],arg[3] };
		add(m);

	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : mel)
	{
		g << e.getid() << "," << e.gettitlul() << "," << e.getartist() << "," << e.getgen() << "\n";
	}
}

void Repo::add(Melodie m)
{
	mel.push_back(m);
	save();
}

int Repo::cauta(int id)
{
	int poz = -1;
	for (int i = 0; i < mel.size(); i++)
		if (mel[i].getid() == id)
			poz = i;
	return poz;
}

void Repo::sterge(int poz)
{
	if (poz != mel.size() - 1)
		for (int i = poz; i < mel.size() - 1; i++)
			mel[i] = mel[i + 1];
	mel.pop_back();
	save();
}

vector<Melodie> Repo::getMel()
{
	return mel;
}