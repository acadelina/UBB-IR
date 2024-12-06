#pragma once
#include<vector>
#include"Domain.h"

class RepoExc
{
	string msg;
public:
	RepoExc(string msg) :msg{ msg } {};
	string getmsg()
	{
		return msg;
	}
};

class Repo
{
	vector<Tractor> lista;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();

	};
	vector<Tractor> getAll();
	void add(Tractor& t);
	void decRoti(int poz);
};