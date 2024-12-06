#include "serviceDis.h"
#include"disciplina.h"
#include"Export.h"
#include<cassert>
#include<algorithm>
#include<vector>
#include"validator.h"
#include<map>
using namespace std;

map<string,int> DisServ::raport()
{
	map<string, int> rap;
	vector<Disciplina>list = getDList();
	for (auto& e : list)
	{
		auto it = rap.find(e.getTip());
		if (it != rap.end())
			rap[e.getTip()]++;
		else
			rap.insert(pair<string, int>(e.getTip(), 1));
	}
	return rap;

}
void DisServ::addDis(const string denum, int ore, const string tip, const string prof)
{

	
	val.validare(denum, ore, tip, prof);
		
	Disciplina newDis{ denum,ore,tip,prof };
	
	repo.add(newDis);
	undoActions.push_back(make_unique<UndoAdd>(newDis, this->repo));
}

void DisServ::modifyDis(const string denum,  int oren, const string tipn, const string profn)
{
	int poz = repo.find(denum);
	Disciplina newDis{ denum,oren,tipn,profn };
	undoActions.push_back(make_unique<UndoModif>(findDis(denum), this->repo));
	repo.modify(poz, newDis);
}

void DisServ::removeDis(const string denum)
{
	const int poz = repo.find(denum);
	undoActions.push_back(make_unique<UndoRemove>(findDis(denum), this->repo));
	repo.remove(poz);
}

const Disciplina DisServ::findDis(const string denum) const
{
	const int poz = repo.find(denum);
	return getDList()[poz];
}

const vector<Disciplina> DisServ::getDList() const noexcept
{
	return repo.getList();
}

size_t DisServ::listSize() const noexcept
{
	return repo.size();
}

vector<Disciplina> DisServ::filtrareCD(const string prof) const
{
	vector<Disciplina> lista = getDList();
	vector<Disciplina> fl;
	//int ad = 0;
	copy_if(lista.begin(), lista.end(), back_inserter(fl), [prof](const Disciplina& dis) {return dis.getProf() == prof; });
	/*for (auto& el : lista)
		if (el.getProf() == prof)
		{
			fl.push_back(el);
			ad = 1;
		}
	if (ad == 0)
		throw 0;*/
	return fl;
}

vector<Disciplina> DisServ::filtrareOre(int ore) const
{
	vector<Disciplina> lista = getDList();
	vector<Disciplina> fl;
	copy_if(lista.begin(), lista.end(), back_inserter(fl), [ore](const Disciplina& dis) {return dis.getOre() == ore; });
	/*nt ad = 0;
	for (auto& el : lista)
		if (el.getOre() == ore)
		{
			fl.push_back(el);
			ad = 1;
		}
	if (ad == 0)
		throw 0;*/
	return fl;
}

bool cmpName(const Disciplina& p1, const Disciplina& p2) {
	return p1.getDenum() < p2.getDenum();
}
bool cmpOre(const Disciplina& p1, const Disciplina& p2) {
	return p1.getOre() < p2.getOre();
}
bool cmpNameType(const Disciplina& p1, const Disciplina& p2) {
	if (p1.getProf() != p2.getProf())
		return p1.getProf() < p2.getProf();
	return p1.getTip() < p2.getTip();
}
vector<Disciplina> DisServ::sortByDenum(int mode) const
{
	vector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	if (mode == 0)
		std::sort(sl.begin(), sl.end(), cmpName);
	else
		std::sort(sl.rbegin(), sl.rend(), cmpName);
	
	return sl;

}

vector<Disciplina> DisServ::sortByOre(int mode) const
{
	vector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	if (mode == 0)
		sort(sl.begin(), sl.end(), cmpOre);
	else
		sort(sl.rbegin(), sl.rend(), cmpOre);
	return sl;

}

vector<Disciplina> DisServ::sortByPT(int mode) const
{
	vector<Disciplina> sl = getDList();
	if (mode != 0 && mode != 1)
		throw 1;
	if (mode == 0)
		sort(sl.begin(), sl.end(), cmpNameType);
	else
		sort(sl.rbegin(), sl.rend(), cmpNameType);

	return sl;

}


const vector<Disciplina>& DisServ::addToContract(const string n) {
	int iterator = this->repo.find(n);
	const Disciplina dis = this->getDList()[iterator];
	this->contract.addCont(dis);
	return this->contract.getAllCont();

}

const vector<Disciplina>& DisServ::fillRandom(int dimension) {
	this->contract.fillContract(dimension, this->getDList());
	return this->contract.getAllCont();
}

const vector<Disciplina>& DisServ::clearContract() {
	this->contract.clearContract();
	return this->contract.getAllCont();
}

const vector<Disciplina>& DisServ::getContract() {
	return this->contract.getAllCont();
}

void  DisServ::undo()
{
	if (undoActions.empty())
		throw RepositoryExceptions("Nu mai sunt actiuni undo");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void testServ()
{
	DisRepo repo;
	Validator val;
	DisServ serv{ repo,val };

	try {
		serv.undo();
	}
	catch (RepositoryExceptions&)
	{
		assert(true);
	}
	serv.addDis("infoo", 4, "t1", "Prof1");

	try {
		serv.addDis("infoo", 4, "t1", "Prof1");
	}
	catch (RepositoryExceptions&)
	{
		assert(true);
	}
	assert(serv.raport().size() == 1);
	
	try {
		serv.addDis("in4", 4, "t1", "prof1");
	}
	catch (ValidationExceptions&)
	{
		assert(true);
	}
	
	assert(serv.getDList()[0].getDenum() == "infoo");
	assert(serv.getDList()[0].getTip() == "t1");

	serv.modifyDis("infoo", 4, "t2", "Prof5");
	//assert(serv.getDList()[0].getDenum() == "infoo");
	assert(serv.getDList()[0].getTip() == "t2");

	vector<Disciplina> fl;
	fl = serv.filtrareCD("Prof5");
	//assert(fl.size() == 1);
	serv.addDis("info", 6, "t1", "Prof1");
	
		fl = serv.filtrareCD("Prof3");
	
	

	fl = serv.filtrareOre(4);
	//assert(fl.size() == 1);
	serv.addDis("inform", 6, "t1", "Prof1");

		fl = serv.filtrareOre(3);
	

	fl = serv.sortByDenum(1);

	assert(fl[0].getDenum() == "inform");
	fl = serv.sortByDenum(0);

	fl = serv.sortByOre(0);
	assert(fl[0].getOre() == 4);
	fl = serv.sortByOre(1);
	fl = serv.sortByPT(0);
	assert(fl[0].getProf() == "Prof1");
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
	Disciplina test = { "",0,"","" };
	test = serv.findDis("infoo");
	assert(test.getDenum() == "infoo");
	assert(test.getProf() == "Prof5");

	serv.removeDis("infoo");
	assert(serv.listSize() == 2);

	//Contract cont;
	assert(serv.addToContract("inform").size()==1);
	assert(serv.clearContract().size() == 0);
	assert(serv.fillRandom(2).size() == 2);
	assert(serv.getContract().size() == 2);

	serv.addDis("informatica", 6, "t3", "Prof1");
	assert(serv.raport().size() == 2);
	//serv.undo();
	//assert(serv.raport().size() == 1);
	serv.modifyDis("informatica", 7, "t4", "PR");
	serv.undo();
	assert(serv.getDList()[1].getOre() == 6);
	serv.removeDis("informatica");
	assert(serv.raport().size() == 1);
	serv.undo();
	assert(serv.raport().size() == 2);
	serv.undo();
	assert(serv.raport().size() == 1);
	
}