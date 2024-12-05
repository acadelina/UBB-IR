#pragma once
#include"Repo.h"
#include"Validator.h"

class Serv {
private:
	Repo& repo;
	Validator& val;
public:
	Serv(Repo& repo, Validator& val):repo{repo},val{val}{}
	void adaugare(int id, string denum, string tip, int roti);
	int nrTip(Tractor t);
	vector<Tractor> getTr();
	vector<Tractor> sort();
	vector<Tractor> filtraret(string tip);
};