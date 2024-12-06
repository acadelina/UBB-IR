#pragma once
#include"Repo.h"

class Serv {
	Repo& rep;
public:
	Serv(Repo& rep):rep{rep}{}
	vector<Telefon> filtm(string model);
	vector<Telefon> filta(int a);
	vector<Telefon> getL();
};