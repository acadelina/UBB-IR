#pragma once
#include"disciplina.h"
#include"Myvector.h"
#include<vector>
#include<string>
using namespace std;

class DisRepo {
private:
	Myvector<Disciplina> dlist;

public:
	DisRepo() noexcept = default;
	DisRepo(const DisRepo& d) = delete;
	/*
	Adaugare disciplina
	precond: d->disciplina
	*/
	void add(const Disciplina& d);

	/*
	Modificare disciplina
	precoond: position->int
			  newD->disciplina
	*/
	void modify(const int& position, const Disciplina& newD);

	/*
	Sterge disciplina
	precond: position->int
	*/
	void remove(const int& position);

	/*
	Cauta disciplina
	precond: denumire->str
	postc: poz->int
	*/
	int find(const string& denumire) const;

	/*
	Lista disciplinelor
	precond:
	postcond: lista
	*/
	const Myvector<Disciplina>& getList() const noexcept;

	/*
	Dimensiunea listei
	preconditii:
	postconditii: dim->int
	*/
	 size_t size() const noexcept;
};

void testRepo();