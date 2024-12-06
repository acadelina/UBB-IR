#pragma once
#include "disciplina.h"
#include "repo.h"
#include"Myvector.h"

#include<vector>
#include<string>
using namespace std;

class DisServ
{
private:
	DisRepo& repo;

public:
	DisServ(DisRepo& r) noexcept: repo{ r } {};
	DisServ(const DisServ& cS) = delete;
	const Myvector<Disciplina>& getDList() const noexcept;
	/*
	Adaugare disciplina
	precnd: denum->str
			ore->int
			tip->str
			prof->str
	postcond:-
	*/
	void addDis(const string& denum, int ore,const string& tip, const string& prof);

	/*
	Modificare disciplina
	precnd: denum->str
			denumn->str
			oren->int
			tipn->str
			profn->str
	postcond:-
	*/
	void modifyDis(const string& denum, const string& denumn, int oren, const string& tipn, const string& profn);

	/*
	Stergere disciplina
	precond: denum->str
	*/
	void removeDis(const string& denum);

	/*
	Cauta disciplina
	precond: denum->str
	postcond: disciplina
	*/
	const Disciplina findDis(const string& denum) const;

	/*
	Dimensiunea listei
	*/
	size_t listSize() const noexcept;

	Myvector<Disciplina> filtrareCD(const string& prof) const;

	Myvector<Disciplina> filtrareOre(int ore) const;

	Myvector<Disciplina> sortByDenum(int mode) const;

	Myvector<Disciplina> sortByOre(int mode) const;

	Myvector<Disciplina> sortByPT(int mode) const;
};

void testServ();