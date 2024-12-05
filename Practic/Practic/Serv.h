#pragma once
#include"repoo.h"
#include"observer.h"

class Serv: public Observable {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	/*
	Functie care returneaza lista de taskuri ordonata
	postcond: vector de taskuri
	*/
	vector<Task> getAll();
	/*
	Functie care returneaza doar taskurile ce contin un programator
	precond: prog-string
	*/
	vector<Task> filtr(string prog);
	/*
	adauga un task nou
	precond: id-int
			stare-string
			p-vector
			desc-string
			*/
	void adaugare(int id, string desc, string stare, vector<string> p);
	/*
	Returneaza taskurile cu o anumita stare
	postcond: vector de taskuri
	*/
	vector<Task> stari(string stare);
	/*
	Modifica starea unui task
	precond: int id
			stare string
			*/
	void modifica(int id, string stare);
};

void testServ();