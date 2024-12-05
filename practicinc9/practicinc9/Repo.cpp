#include"Repo.h"
#include<sstream>
#include<fstream>

void Repo::add(Task& t)
{
	lista.push_back(t);
	save();
}

void Repo::load()
{
	ifstream f(filename);
	string linie;
	while (getline(f, linie))
	{
		auto ss = stringstream(linie);
		string cuv;
		vector<string> arg;
		int ind = 0;
		vector<string> pr;
		while (getline(ss, cuv, ';'))
		{
			
			if (ind == 3)
			{
				auto aa = stringstream(cuv);
				string aux;
				while (getline(aa, aux, ','))
					pr.push_back(aux);
			}
			else
				arg.push_back(cuv);
			ind++;

		}
		Task t{ stoi(arg[0]),arg[1],pr,arg[2] };
		lista.push_back(t);
	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : lista)
	{
		g << e.getid() << ";" << e.getdesc() << ";" << e.getstare() << ";";
		for (auto a : e.getprog())
			g << a << ",";
		g << "\n";
	}
}

bool Repo::search(string p, Task t)
{
	for (auto e : t.getprog())
		if (e == p)
			return true;
	return false;
}

void Repo::changes(int poz, string st)
{
	lista[poz].setstare(st);
	save();
}

int Repo::cauta(int id)
{
	int poz = -1;
	for (int i=0;i<lista.size();i++)
	{
		if (lista[i].getid() == id)
		{
			poz = i;
			break;
		}
	}
	return poz;
}

vector<Task> Repo::getAll()
{
	return lista;
}


