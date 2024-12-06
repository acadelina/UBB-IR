#pragma once
#include"Melodie.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class FileRepo {
private:
	string filename;
	vector<Produs> produse;

	void load();
	void save();
public:
	FileRepo(string filename) :filename{ filename } {
		load();
	}

	bool validareId(int id);

	void add(Produs& p);

	void modifica(int pos, Produs& p);

	void sterge(int pos);

	int cauta(Produs& p);

	vector<Produs>& getAll();

};

class RepoExceptions {
	string mesaj;
public:
	RepoExceptions(string mesaj):mesaj{mesaj}{}

	string getMsg() { return this->mesaj; }
};