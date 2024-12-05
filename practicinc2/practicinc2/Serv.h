#pragma once
#include"Repo.h"
#include<map>

class Serv {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	vector<Melodie> sort();
	vector<Melodie> getAll();
	void adauga(int id, string t, string a, string g);
	void stergere(int id);
	map<string, int> sameA();
	map<string, int> sameG();

};