#include "service.h"
#include"validator.h"
#include<cassert>
using namespace std;

void DisServ::addDis(const string& denum, int ore, const string& tip, const string& prof)
{
	
	if (repo.find(denum) != -1)
		throw 1;
	if (validare(denum, ore, tip, prof) == 0)
		throw 2;
	Disciplina newDis{ denum,ore,tip,prof };
	repo.add(newDis);
}

void DisServ::modifyDis(const string& denum, const string& denumn, int oren, const string& tipn, const string& profn)
{
	int poz = repo.find(denum);
	Disciplina newDis{ denumn,oren,tipn,profn };
	repo.modify(poz, newDis);

}

void DisServ::removeDis(const string& denum)
{
	const int poz = repo.find(denum);
	repo.remove(poz);
}

const Disciplina DisServ::findDis(const string& denum) const
{
	const int poz = repo.find(denum);
	return getDList().get(poz);
}

const Myvector<Disciplina>& DisServ::getDList() const noexcept
{
	return repo.getList();
}

size_t DisServ::listSize() const noexcept
{
	return repo.size();
}

Myvector<Disciplina> DisServ::filtrareCD(const string& prof) const
{
	Myvector<Disciplina> lista = getDList();
	Myvector<Disciplina> fl;
	int ad = 0;
	for(int i=0;i<lista.size();i++)
		if (lista.get(i).getProf() == prof)
		{
			fl.add(lista.get(i));
			ad = 1;
		}
	if (ad == 0)
		throw 0;
	return fl;
}

Myvector<Disciplina> DisServ::filtrareOre(int ore) const
{
	Myvector<Disciplina> lista = getDList();
	Myvector<Disciplina> fl;
	int ad = 0;
	for (int i = 0; i < lista.size(); i++)
		if (lista.get(i).getOre() == ore)
		{
			fl.add(lista.get(i));
			ad = 1;
		}
	if (ad == 0)
		throw 0;
	return fl;
}

Myvector<Disciplina> DisServ::sortByDenum(int mode) const
{
	Myvector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	sl.sort(mode, 'd');
	return sl;

}

Myvector<Disciplina> DisServ::sortByOre(int mode) const
{
	Myvector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	sl.sort(mode, 'o');
	return sl;

}

Myvector<Disciplina> DisServ::sortByPT(int mode) const
{
	Myvector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	sl.sort(mode, 'p');
	return sl;

}
void testServ()
{
	DisRepo repo;
	DisServ serv{ repo };

	serv.addDis("info", 4, "t1", "Prof1");
	
	try {
		serv.addDis("info", 4, "t1", "Prof1");
	}
	catch (...)
	{
		assert(true);
	}
	try {
		serv.addDis("in4", 4, "t1", "prof1");
	}
	catch (...)
	{
		assert(true);
	}
	assert(serv.getDList().get(0).getDenum() == "info");
	assert(serv.getDList().get(0).getTip() == "t1");

	serv.modifyDis("info","infoo", 4, "t2", "Prof5");
	assert(serv.getDList().get(0).getDenum() == "infoo");
	assert(serv.getDList().get(0).getTip() == "t2");

	Myvector<Disciplina> fl;
	fl= serv.filtrareCD("Prof5");
	//assert(fl.size() == 1);
	serv.addDis("info", 6, "t1", "Prof1");
	try
	{
		fl = serv.filtrareCD("Prof3");
	}
	catch (...)
	{
		assert(true);
	}
	
	fl = serv.filtrareOre(4);
	//assert(fl.size() == 1);
	serv.addDis("inform", 6, "t1", "Prof1");
	try
	{
		fl = serv.filtrareOre(3);
	}
	catch (...)
	{
		assert(true);
	}

	fl = serv.sortByDenum(1);
	
	assert(fl.get(0).getDenum() == "inform");
	fl = serv.sortByDenum(0);

	fl = serv.sortByOre(0);
	assert(fl.get(0).getOre() == 4);
	fl = serv.sortByOre(1);
	fl = serv.sortByPT(0);
	assert(fl.get(0).getProf() == "Prof1");
	fl = serv.sortByPT(1);
	try {
		fl = serv.sortByDenum(-1);
	}
	catch (...)
	{
		assert(true);

	}

	try {
		fl = serv.sortByOre(-1);
	}
	catch (...)
	{
		assert(true);

	}
	try {
		fl = serv.sortByPT(-1);
	}
	catch (...)
	{
		assert(true);

	}
	Disciplina test = {"",0,"",""};
	test = serv.findDis("infoo");
	assert(test.getDenum() == "infoo");
	assert(test.getProf() == "Prof5");

	serv.removeDis("infoo");
	assert(serv.listSize() == 2);
	
}