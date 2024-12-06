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
	vector<Joc> l;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	void add(Joc& j);
	vector<Joc> getAll();
	void modifica(Joc& j);
};

void testRepo();