#pragma once
#include "disciplina.h"
#include "repoDis.h"
#include"validator.h"
#include"contract.h"
#include"undo.h"
#include<map>

#include<vector>
#include<string>

using namespace std;

class DisServ
{
private:
	RepoAbs& repo;
	Validator& val;
	vector<unique_ptr<ActiuneUndo>> undoActions;
	Contract contract;

public:
	DisServ(RepoAbs& r, Validator& v) noexcept : repo{ r }, val { v } {};
	DisServ(const DisServ& cS) = delete;
	map<string, int> raport();
	const vector<Disciplina> getDList() const noexcept;
	/*
	Adaugare disciplina
	precnd: denum->str
			ore->int
			tip->str
			prof->str
	postcond:-
	*/
	void addDis(const string denum, int ore, const string tip, const string prof);

	/*
	Modificare disciplina
	precnd: denum->str
			denumn->str
			oren->int
			tipn->str
			profn->str
	postcond:-
	*/
	void modifyDis(const string denum, int oren, const string tipn, const string profn);

	/*
	Stergere disciplina
	precond: denum->str
	*/
	void removeDis(const string denum);

	/*
	Cauta disciplina
	precond: denum->str
	postcond: disciplina
	*/
	const Disciplina findDis(const string denum) const;

	/*
	Dimensiunea listei
	*/
	size_t listSize() const noexcept;

	/*
	Functie care returneaza disciplinele filtrate dupa prof*/
	vector<Disciplina> filtrareCD(const string prof) const;

	/*
	Functie care returneaza disciplinele filtrate dupa ore
	*/
	vector<Disciplina> filtrareOre(int ore) const;

	/*
	Functie care sorteaza disciplinele sortate dupa denumire
	*/
	vector<Disciplina> sortByDenum(int mode) const;

	/*
	Functie care returneaza disciplinele sortate dupa ore
	*/
	vector<Disciplina> sortByOre(int mode) const;

	/*
	functie care returneaza disciplinele sortate dupa profesor si tip
	*/
	vector<Disciplina> sortByPT(int mode) const;

	/*
	Functie care adauga o disciplina data in contract
	*/
	const vector<Disciplina>& addToContract(string denum);

	/*
	Functie care adauga un numar de discipline in contract
	*/
	const vector<Disciplina>& fillRandom(int dim);

	/*
	Functie care sterge disciplinele din contract
	*/
	const vector<Disciplina>& clearContract();

	/*
	Functie car returneaza contractul curent
	*/
	const vector<Disciplina>& getContract();

	/*
	Functie de undo
	*/
	void undo();
};

void testServ();