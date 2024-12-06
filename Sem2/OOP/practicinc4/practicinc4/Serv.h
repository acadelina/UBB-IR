#pragma once
#include"Repo.h"
#include<map>
#include"observer.h"

class Serv :public Observable{
	Repo& rep;
public:
	explicit Serv(Repo& rep) :rep{ rep } {};
	vector<Task> getAll();
	vector<Task> sort();
	vector<Task> search(string p);
	map<string, vector<Task>> stari();
	void adaugare(int id, string d, vector<string> p, string st);
	void schimbs(int id,string n);
};
