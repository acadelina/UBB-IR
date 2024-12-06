#include<Repo.h>
#include<sstream>
#include<fstream>
#include<cassert>

void Repo::load()
{
	ifstream f(filename);
	string linie;
	while (getline(f, linie))
	{
		auto ss = stringstream(linie);
		vector<string> arg;
		string cuv;
		while (getline(ss, cuv, ','))
		{
			arg.push_back(cuv);
		}
		Melodie m{ stoi(arg[0]),arg[1],arg[2],stoi(arg[3]) };
		mel.push_back(m);
	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto m : mel)
	{
		g << m.getid() << "," << m.gettitlu() << "," << m.getartist() << "," << m.getrank() << "\n";
	}
}

int Repo::cauta(int id)
{
	int poz = -1;
	for (int i = 0; i < mel.size(); i++)
		if (mel[i].getid() == id)
			poz = i;
	return poz;
}

void Repo::del(int id)
{
	int poz = cauta(id);
	if (poz != mel.size() - 1)
		for (int i = poz; i < mel.size() - 1; i++)
			mel[i] = mel[i + 1];
	mel.pop_back();
	save();
		
}

void Repo::modif(int id, string titlu, int rank)
{
	int poz = cauta(id);
	mel[poz].setrank(rank);
	mel[poz].settitlu(titlu);
	save();
}

vector<Melodie> Repo::getAll()
{
	return mel;
}

void testRepo()
{
	Repo rep{ "test.txt" };
	assert(rep.getAll().size() == 3);
	assert(rep.cauta(3) == 0);
	assert(rep.cauta(11) == -1);
	rep.modif(3, "t", 10);
	assert(rep.getAll()[0].gettitlu() == "t");
	assert(rep.getAll()[0].getrank() == 10);
	rep.del(3);
	assert(rep.getAll().size() == 2);

}