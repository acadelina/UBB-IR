#pragma once
#include"Domain.h"

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
	vector<Task> lista;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	};
	void add(Task& t);
	bool cauta(Task t, string p);
	vector<Task> getT() {
		return lista;
	}
	void change(int poz, string s);
};