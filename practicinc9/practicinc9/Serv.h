#pragma once
#include"Repo.h"
#include"Observer.h"

class Serv:public Observable {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	vector<Task> sort();
	void adaugare(int id, string desc, vector<string> v, string stare);
	void modificare(int id, string stare);
	vector<Task> filtrare(string prog);
	vector<Task> stari(string stare);
};