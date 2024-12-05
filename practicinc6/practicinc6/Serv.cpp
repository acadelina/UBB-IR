#include"Serv.h"
#include<algorithm>
using namespace std;

void Serv::adaugare(int id, int d, string t, string j, string s)
{
	Joc jo{ id,d,t,j,s };
	rep.add(jo);
}

void Serv::modificare(int id, int d, string t, string j, string s)
{
	Joc jo{ id,d,t,j,s };
	rep.modifica(jo);
}

vector<Joc> Serv::sort()
{
	vector<Joc> v = rep.getAll();
	std::sort(v.begin(), v.end(), [](Joc& j1, Joc& j2) {
		return j1.getstare() > j2.getstare();
		});
	return v;
}

