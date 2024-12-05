#pragma once
#include"Validator.h"
#include"Repo.h"
#include"observer.h"
#include<map>

class Serv:public Observable {
	Repo& rep;
	Validator val;
public:
	Serv(Repo& rep, Validator val) :rep{ rep }, val{ val } {};
	vector<Produs> getP();
	vector<Produs> sortP();
	vector<Produs> filtr(int pret);
	map<string, int> tipuri();
	void adauga(int id, string nume, string tip, double pret);
};