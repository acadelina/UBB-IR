#include"Service.h"
#include<algorithm>

void Serv::adaugare(int id, string denum, string tip, int roti)
{
	val.valideaza(id, denum, tip, roti);
	Tractor t{ id,denum,tip,roti };
	repo.add(t);
}

vector<Tractor> Serv::getTr()
{
	return repo.getAll();
}

int Serv::nrTip(Tractor t)
{
	vector<Tractor> tr = getTr();
	int nr = 0;
	for (auto& e : tr)
	{
		if (e.getTip() == t.getTip())
			nr++;
	}
	return nr;
}

bool cmpD(Tractor& t1, Tractor& t2)
{
	return t1.getDenum() < t2.getDenum();
}

vector<Tractor> Serv::sort()
{
	vector<Tractor> tr = getTr();
	std::sort(tr.begin(), tr.end(), cmpD);
	return tr;
}

vector<Tractor> Serv::filtraret(string tip)
{
	vector<Tractor> tr = getTr();
	vector<Tractor> filt;

	copy_if(tr.begin(), tr.end(), back_inserter(filt), [tip](Tractor& t) {return t.getTip() == tip; });

	return filt;
}