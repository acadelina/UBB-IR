#include"Repo.h"
#include<fstream>
#include<sstream>

vector<Melodie> Repo::getMel()
{
	return mel;
}
void Repo::load()
{
	ifstream f(filename);
	string linie;
	while (getline(f, linie))
	{
		if (linie.empty())
			continue;
		auto ss = stringstream(linie);
		vector<string> arg;
		string cuv;
		while (getline(ss, cuv, ','))
		{
			arg.push_back(cuv);
		}
		Melodie m{ stoi(arg[0]),arg[1],arg[2],stoi(arg[3]) };
		add(m);

	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : mel)
	{
		g << e.getid() << "," << e.gettitlu() << "," << e.getartist() << "," << e.getrank() << "\n";
	}
}

void Repo::add(Melodie m)
{
	mel.push_back(m);
	save();
}

void Repo::del(int poz)
{
	
	if (poz == -1)
		throw RepoExc("Melodie inexistenta");
	if(poz!=mel.size()-1)
	for (int i = poz; i < mel.size() - 1; i++)
		mel[i] = mel[i + 1];
	mel.pop_back();
	save();

}

void Repo::schimbR(int m, int r)
{
	mel[m].setrank(r);
	save();
}

void Repo::schimbT(int m, string t)
{
	mel[m].settitlu(t);
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