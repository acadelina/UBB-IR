#include"Serv.h"
#include<algorithm>

vector<Rochie> Serv::getL()
{
	return rep.getAll();
}

bool cmpm(Rochie r1, Rochie r2)
{
	return r1.getmarime() < r2.getmarime();
}

vector<Rochie> Serv::sortM()
{
	vector<Rochie> r = getL();
	std::sort(r.begin(), r.end(), cmpm);
	return r;
}


bool cmpp(Rochie r1, Rochie r2)
{
	return r1.getpret() < r2.getpret();
}

vector<Rochie> Serv::sortp()
{
	vector<Rochie> r = getL();
	std::sort(r.begin(), r.end(), cmpp);
	return r;
}

void Serv::adauga(int cod, string d, string m, int p, bool dis)
{
	Rochie r{ cod,d,m,p,dis };
	rep.add(r);
}

void Serv::Inchiriere(string d, string m, int p)
{
	Rochie r = rep.cauta(d, m, p);
	//Rochie r{ cod,d,m,p,dis };
	if (r.getdisp() == false)
		throw ServExc("Rochie indisponibila");
	rep.inchiriere(d,m,p);
}
