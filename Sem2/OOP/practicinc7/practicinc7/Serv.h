#pragma once
#include<map>
#include"Repo.h"
#include<cassert>
#include"Observer.h"

class Serv:public Observable {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	/*functie care adauga un produs
	* id-int
	* nume-string
	* tip-string
	* pret-double
	*/
	void adauga(int id, string nume, string tip, double pret);

	/*
	Functie care returneaz alista de produse sortata
	*/
	vector<Produs> sort();

	map<string, int> tipuri();


};