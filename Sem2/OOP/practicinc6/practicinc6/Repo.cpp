#include"Repo.h"
#include<sstream>
#include<fstream>
#include<cassert>

void Repo::add(Joc& j)
{
	string msg = "";
	if (j.getdim() < 3 || j.getdim() > 5)
		msg += "Dimensiune invalida\n";
	if (j.getjuc() != "O" && j.getjuc() != "X")
		msg += "Jucator invalid\n";
	for (auto e : j.gettabla())
	{
		if (e != 'X' && e != 'O' && e != '-')
		{
			msg += "Tabla incorecta\n";
			break;
		}
	}
	if (j.getstare() != "Neinceput" && j.getstare() != "In derulare" && j.getstare() != "Terminat")
		msg += "Stare invalida\n";
	if (msg != "")
		throw RepoExc(msg);
	l.push_back(j);
	save();
}

void Repo::modifica(Joc& j)
{
	string msg = "";
	if (j.getdim() < 3 || j.getdim() > 5)
		msg += "Dimensiune invalida\n";
	if (j.getjuc() != "O" && j.getjuc() != "X")
		msg += "Jucator invalid\n";
	for (auto e : j.gettabla())
	{
		if (e != 'X' && e != 'O' && e != '-')
		{
			msg += "Tabla incorecta\n";
			break;
		}
	}
	if (j.getstare() != "Neinceput" && j.getstare() != "In derulare" && j.getstare() != "Terminat")
		msg += "Stare invalida\n";
	if (msg != "")
		throw RepoExc(msg);

	int poz = -1;
	for (int i = 0; i < l.size(); i++)
		if (l[i].getid() == j.getid())
			poz = i;
	l[poz].setdim(j.getdim());
	l[poz].setid(j.getid());
	l[poz].setjuc(j.getjuc());
	l[poz].setstare(j.getstare());
	l[poz].settabla(j.gettabla());
	save();
	
}

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
		Joc j{ stoi(arg[0]),stoi(arg[1]),arg[2],arg[3],arg[4] };
		l.push_back(j);
	}
}


void Repo::save()
{
	ofstream g(filename);
	for (auto e : l)
		g << e.getid() << "," << e.getdim() << "," << e.gettabla() << "," << e.getjuc() << "," << e.getstare() << "\n";
}

vector<Joc> Repo::getAll()
{
	return this->l;
}

void testRepo()
{
	Repo r{ "test.txt" };
	assert(r.getAll().size() == 0);
	Joc j1{ 1,3,"X-OXO-XOO","X","Terminat"};
	Joc j2{ 2,3,"X-OXX-XOO","O","In derulare" };
	r.add(j1);
	r.add(j2);
	assert(r.getAll().size() == 2);
	Joc j3{ 2,3,"X-OXX-XOO","O","Terminat" };
	r.modifica(j3);
	assert(r.getAll()[1].getstare() == "Terminat");
}