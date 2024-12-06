#include"Repo.h"
#include<sstream>
#include<fstream>

void Repo::load()
{
	ifstream f(filename);
	string line;
	while (getline(f, line)) {
		string descriere, stare;
		int id, programatori;
		stringstream linestream(line);
		string curent;
		int nr = 0;
		while (getline(linestream, curent, ';')) {
			if (nr == 0)
				id = stoi(curent);
			if (nr == 1)
				descriere = curent;
			if (nr == 2)
				stare = curent;
			if (nr == 3)
			{
				string current_2;
				stringstream stream_2(curent);
				vector<string>lst;
				while (getline(stream_2, current_2, ',')) {
					lst.push_back(current_2);
				}
				lista.push_back(Task(id, descriere, lst,stare));
			}
			nr++;
		}
	}
	f.close();
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : lista)
	{
		g << e.getid() << ";" << e.getdesc() << ";"<<e.getstare()<<";";
		vector<string> l = e.getprog();
		for (auto p : l)
			g << p << ",";
		g << "\n";
	}
}

void Repo::add(Task& t)
{
	string msg = "";
	if (t.getdesc() == "")
		msg += "descriere vida\n";
	if (t.getprog().size() < 1 || t.getprog().size() > 4)
		msg += "numar incorect de proramatori\n";
	if (t.getstare() != "open" && t.getstare() != "inprogress" && t.getstare() != "closed")
		msg += "stare invalida\n";
	for (auto a : lista)
		if (a.getid() == t.getid())
		{
			msg += "Id existent deja";
			break;
		}
	if (msg != "")
		throw RepoError(msg);

	lista.push_back(t);
	save();
}

bool Repo::cauta(Task t, string p)
{
	vector<string> a = t.getprog();
	for (auto pr : a)
		if (pr == p)
			return true;
	return false;
}

void Repo::change(int poz, string s)
{
	lista[poz].setstare(s);
	save();
}