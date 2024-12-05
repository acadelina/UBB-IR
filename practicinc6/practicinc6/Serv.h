#pragma once
#include"Repo.h"

class Serv {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	vector<Joc> sort();
	void adaugare(int id, int d, string t, string j, string s);
	void modificare(int id, int d, string t, string j, string s);

};