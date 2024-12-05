#include"Repo.h"
#include<fstream>
#include<sstream>
void Repo::load()
{
	ifstream fin(filename);
	string linie;
	while (getline(fin, linie))
	{
		auto ss = stringstream(linie);
		vector<string> arg;
		string a;
		while (getline(ss, a, ';'))
			arg.push_back(a);
		Melodie m{ stoi(arg[0]),arg[1],arg[2],arg[3] };
		add(m);

	}

}

void Repo::save()
{
	ofstream fout(filename);
	vector<Melodie>  m = melodii;
	for (auto a : m)
	{
		fout << a.getid() << ";" << a.gettitlu() << ";" << a.getartist() << ";" << a.getgen() << "\n";

	}
}

void Repo::add(Melodie m)
{
	melodii.push_back(m);
	save();
}

int Repo::cauta(int m)
{
	vector<Melodie> mel=melodii;
	int poz = -1;
	for (int i=0;i<mel.size();i++)
	{
		if (mel[i].getid() == m)
		{
			poz = i;
			break;
		}
		
	}
	return poz;
}
void Repo::del(int id)
{
	
	if (id == -1)
		throw RepoExc("Melodie inexistenta");
	int dim = melodii.size();
	if (id != dim - 1)
	{
		for (int i = id; i<dim - 1; i++)
		{
			melodii[i] = melodii[i + 1];
		}
		
	}melodii.pop_back();
	save();
}

vector<Melodie> Repo::getAll()
{
	return melodii;
}