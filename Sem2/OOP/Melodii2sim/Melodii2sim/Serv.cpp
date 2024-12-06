#include"Serv.h"
#include<algorithm>

void Serv::adauga(int id, string titlu, string artist, string gen)
{
	Melodie m{ id,titlu,artist,gen };
	rep.add(m);
}

void Serv::sterge(int id)
{
	int poz = rep.cauta(id);
	rep.del(poz);
}

vector<Melodie> Serv::getL()
{
	return rep.getAll();
}

bool cmpA(Melodie& m1, Melodie& m2)
{
	return m1.getartist() < m2.getartist();
}
vector<Melodie> Serv::sort()
{
	vector<Melodie> mel = getL();
	std::sort(mel.begin(), mel.end(), cmpA);
	return mel;
}

int Serv::nrart(string art)
{
	int n = 0;
	vector<Melodie> mel = getL();
	for (auto a : mel)
	{
		if (a.getartist() == art)
			n++;
	}
	return n;
}

int Serv::nrgen(string art)
{
	int n = 0;
	vector<Melodie> mel = getL();
	for (auto a : mel)
	{
		if (a.getgen() == art)
			n++;
	}
	return n;
}