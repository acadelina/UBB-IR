#include"Service.h"
#include<algorithm>

void Serv::adaugare(int id, string nume, string tip, int pret, string producator)
{
	val.validareProdus(nume, tip, pret, producator);
	Produs newP{ id,nume,tip,pret,producator };
	repo.add(newP);

}

void Serv::modificare(int id, string nume, string tip, int pret, string producator)
{
	val.validareProdus(nume, tip, pret, producator);
	Produs newP{ id,nume,tip,pret,producator };
	int pos = repo.cauta(newP);
	repo.modifica(pos,newP);

}

void Serv::stergere(int id, string nume, string tip, int pret, string producator)
{
	Produs newP{ id,nume,tip,pret,producator };
	int pos = repo.cauta(newP);
	repo.sterge(pos);
}


vector<Produs> Serv::filtrareNume(string nume)
{
	vector<Produs> produse = repo.getAll();
	vector<Produs> filt;

	copy_if(produse.begin(), produse.end(), back_inserter(filt), [nume](const Produs& p) {return p.getNume() == nume; });
	return filt;
}

vector<Produs> Serv::filtrarePret(int pret)
{
	vector<Produs> produse = repo.getAll();
	vector<Produs> filt;

	copy_if(produse.begin(), produse.end(),back_inserter(filt), [pret](const Produs& p) {return p.getPret() == pret; });
	return filt;
}

bool cmpNume(const Produs& p1, const Produs& p2)
{
	return p1.getNume() < p2.getNume();
}
vector<Produs> Serv::sortareNume(int o)
{
	vector<Produs> pr = getList();
	if (o == 0)
	{
		sort(pr.begin(), pr.end(), cmpNume);
	}
	else
	{
		sort(pr.rbegin(), pr.rend(), cmpNume);
	}
	return pr;
}

bool cmpPret(Produs& p1, Produs& p2)
{
	return p1.getPret() < p2.getPret();
}


vector<Produs> Serv::sortarePret(int o)
{
	vector<Produs> pr = repo.getAll();
	if (o == 0)
	{
		std::sort(pr.begin(), pr.end(), cmpPret);
	}
	else
	{
		std::sort(pr.rbegin(), pr.rend(), cmpPret);
	}
	return pr;
}

vector<Produs> Serv::getList()
{
	return repo.getAll();
}