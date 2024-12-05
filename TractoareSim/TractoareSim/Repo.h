#pragma once
#include"Tractoare.h"
#include<vector>
#include<fstream>

class Repo {
private:
	vector<Tractor> tractoare;
	string filename;
	void save();
	void load();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	void add(Tractor& t);
	vector<Tractor>& getAll();

};

class RepoException {
private:
	string msj;
public:
	RepoException(string msj) :msj{ msj }{}
	string getMsj()
	{
		return this->msj;
	}
};