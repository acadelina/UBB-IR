#pragma once
#include"Repo.h"

class Serv {
	Repo& rep;
public:
	Serv(Repo& rep):rep{rep}{}

	void adauga(int id, string titlu, string art, string gen);

	void sterge(int id);

	vector<Melodie> getL();

	vector<Melodie> sort();
	int nrart(string art);
	int nrgen(string art);
};