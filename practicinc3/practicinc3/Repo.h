#pragma once
#include"Domain.h"
#include<vector>


class RepoError {
	string msg;
public:
	RepoError(string msg) :msg{ msg } {};
	string getmsg()
	{
		return msg;
	}
};

class Repo {
	vector<Produs> produse;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	};
	void add(Produs& p);
	vector<Produs> getAll();
};