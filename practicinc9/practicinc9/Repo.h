#pragma once
#include"Domain.h"

class Repo {
	vector<Task> lista;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	void add(Task& t);
	bool search(string p, Task t);
	void changes(int poz,string st);
	int cauta(int id);
	vector<Task> getAll();
};