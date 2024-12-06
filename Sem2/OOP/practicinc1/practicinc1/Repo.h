#pragma once
#include"melodie.h"
#include<vector>

class RepoExc {
	string msj;
	string getMsj() {
		return this->msj;
	}
public:
	RepoExc(string msj) :msj{ msj } {};

};
class Repo {
	string filename;
	vector<Melodie> mel;
	void load();
	void save();
	
public:
	Repo(string filename) :filename{ filename } {
		load();
	};
	int cauta(int id);
	void add(Melodie m);
	void del(int poz);
	void schimbR(int m, int r);
	vector<Melodie> getMel();
	void schimbT(int m,string t);
};