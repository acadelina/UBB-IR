#pragma once
#include"Repo.h"
#include"map"

class Serv {
	Repo& repo;
public:
	Serv(Repo& rep) :repo{ rep } {};
	vector<Tractor> getAll();
	vector<Tractor> sort();
	void adaugare(int id, string denum, string tip, int roti);
	void decrement(int id);
	map<string, int> sametip();
	int roti(int poz);
};