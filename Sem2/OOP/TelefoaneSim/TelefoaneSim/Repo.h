#pragma once
#include"Domain.h"
#include<vector>

class RepoException {
	string msj;
public:
	RepoException(string msj) :msj{ msj } {
	}
	string getmsj()
	{
		return this->msj;
	}
};
class Repo {
	string filename;
	vector<Telefon> tel;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	void add(Telefon& t);
	vector<Telefon> getAll();

};

void testRepo();