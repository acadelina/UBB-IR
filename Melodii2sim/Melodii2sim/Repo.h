#pragma once
#include"Domain.h"
#include<vector>

class RepoExc {
	string msg;
public:
	RepoExc(string msg) :msg{ msg }{}
	string getmsg() {
		return this->msg;
	}
};
class Repo {
	string filename;
	vector<Melodie> melodii;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();

	}
	void add(Melodie m);
	void del(int m);
	int cauta(int m);
	vector<Melodie> getAll();
};