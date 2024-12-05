#include"repoo.h"
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
		string cuv;
		vector<string> arg;
		int ind=0;
		vector<string> prog;
		while (getline(ss, cuv, ';'))
		{
			
			if (ind == 3)
			{
				auto aa = stringstream(cuv);
				string sec;

				while (getline(aa, sec, ','))
				{
					prog.push_back(sec);
				}
			}
			else
				arg.push_back(cuv);
			ind++;
			
		}
		Task t{ stoi(arg[0]),arg[1],arg[2],prog };
		v.push_back(t);
	}
}

void Repo::save()
{
	ofstream g(filename);
	for (auto e : v)
	{
		g << e.getid() << ";" << e.getdesc() << ";" << e.getstare() << ";";
		for (auto a : e.getprog())
			g << a << ",";
		g << "\n";
	}
}

void Repo::validare(Task& t)
{
	string msg = "";
	for(auto a:v)
		if (a.getid() == t.getid())
		{
			msg += "Id invalid\n";
			break;
		}
	if (t.getdesc() == "")
		msg += "Descreiere invalida\n";
	if (t.getstare() != "open" && t.getstare() != "closed" && t.getstare() != "inprogress")
		msg += "Stare invalida\n";
	if (t.getprog().size() < 1 || t.getprog().size() > 4)
		msg += "Numar invalid de programatori";
	if (msg != "")
		throw RepoExc(msg);
}

void Repo::add(Task& t)
{
	validare(t);
	v.push_back(t);
	save();
}

void Repo::schimbStare(int id, string stare)
{
	int poz = cauta(id);
	v[poz].setstare(stare);
	save();
}

int Repo::cauta(int id)
{
	int poz = -1;
	for (int i=0;i<v.size();i++)
	{
		if (v[i].getid() == id)
			poz = i;
	}
	return poz;
}

bool Repo::searchP(Task t, string p)
{
	for (auto a : t.getprog())
	{
		if (a == p)
			return true;
	}
	return false;
}

vector<Task> Repo::getT()
{
	return v;

}

/*
2;desc2;open;pr1,pr2,
3;desc3;open;pr1,pr3,
4;desc1;inprogress;pr3,
5;desc4;inprogress;pr2,pr3,
*/
void testRepo()
{
	Repo rep{ "test.txt" };
	assert(rep.getT().size() == 4);
	Task t{ 2,"","",{"p","pp","ppp","pppp","ppppp"}};
	try {
		rep.validare(t);
	}
	catch (RepoExc& r)
	{
		assert(r.getmsg() != "");
		assert(true);
	}
	Task t1{ 1,"d","open",{"p"} };
	rep.add(t1);
	assert(rep.getT().size() == 5);
	int p = rep.cauta(5);
	assert(p == 3);
	rep.schimbStare(5, "open");
	p = rep.cauta(5);
	assert(rep.getT()[p].getstare() == "open");
	assert(rep.searchP(t1, "p"));



}