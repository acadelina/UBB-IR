#pragma once
#include"Domain.h"
#include<vector>

class RepoExc {
	string msg;
public:
	RepoExc(string msg) :msg{ msg } {};
	string getmsg()
	{
		return msg;
	}
};

class Repo {
	vector<Produs> v;
	string filename;
	//functie care incarca datele
	void load();
	//functie care salveaza datele
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	//functie de adaugare a unui produs in lista
	//prec:p -produs
	void add(Produs& p);
	//functie care returneaza vectorul de produse
	vector<Produs> getAll();
};