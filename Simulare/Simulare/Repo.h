#pragma once
#include"Domain.h"
#include<vector>

class Repo {
	string filename;
	vector<Rochie> list;
	//functie de salvare in fisier
	void save();
	//functie de incarcare din fisier
	void load();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	//functie de inchiriere rochie
	void inchiriere(string d, string m, int p);
	//ret lista de rochii
	vector<Rochie> getAll();
	//adauga rochie
	void add(Rochie r);
	//cauta rochie
	Rochie cauta(string d, string m, int p);
};

void testRepo();