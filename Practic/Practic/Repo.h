#pragma once
#include"Domain.h";


class RepoExc {
	string msg;
public:
	RepoExc(string msg) :msg{ msg } {};
	string getmsg()
	{
		return this->msg;
	};
};
class Repo {
	vector<Task> v;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	};
	void add(Task& t);
	void validare(Task& t);
	void schimbStare(int id, string stare);
	int cauta(int id);
	bool searchP(Task t, string p);
	vector<Task> getT();
};