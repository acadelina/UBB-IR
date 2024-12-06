#pragma once
#include"Domain.h"
#include<vector>

class Repo {
	string filename;
	vector<Melodie> mel;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	void add(Melodie m);
	void sterge(int poz);
	int cauta(int id);
	vector<Melodie> getMel();
};