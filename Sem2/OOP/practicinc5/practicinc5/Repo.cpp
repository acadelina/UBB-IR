#include"Repo.h"
#include<sstream>
#include<fstream>
using namespace std;

void Repo :: load()
{
	ifstream f(filename);
	string line;
	while (getline(f, line))
	{
		auto ss = stringstream(line);
		vector<string> arg;
		string cuv;
		while (getline(ss, cuv, ','))
		{
			arg.push_back(cuv);
		}
		Tractor t{ stoi(arg[0]),arg[1],arg[2],stoi(arg[3]) };
		add(t);
	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : lista)
	{
		g << e.getid() << "," << e.getdenum() << "," << e.gettip() << "," << e.getRoti() << "\n";
	}
}

void Repo::add(Tractor& t)
{
	string msg = "";
	if (t.getdenum() == "")
		msg += "Denumirea nu poate fi nula\n";
	if (t.gettip() == "")
		msg += "Tipul nu poate fi vid\n";
	int nr = t.getRoti();
	if (nr % 2 == 1 || nr < 2 || nr>16)
		msg += "Nr de roti invalid\n";
	for (auto a : lista)
	{
		if (a.getid() == t.getid())
		{
			msg += "Id existent\n";
			break;
		}
	}
	if (msg != "")
		throw RepoExc(msg);
	lista.push_back(t);
	save();
}

vector<Tractor> Repo::getAll()
{
	return lista;
}

void Repo::decRoti(int poz)
{
	lista[poz].setRoti(lista[poz].getRoti() - 2);
	save();
}