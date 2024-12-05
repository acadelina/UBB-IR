#pragma once
#include"Repo.h"
#include"Domain.h"

class ServExc {
	string msj;
public:
	ServExc(string msj):msj{msj}{}
	string getmsj()
	{
		return this->msj;
	}
};
class Serv {
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {}
	//returneaz alista
	vector<Rochie> getL();
	//adauga o rochie in lista
	void adauga(int cod, string denu, string marime, int pret, bool disp);
	//sorteaza dupa marime
	vector<Rochie> sortM();
	//sorteaza dupa pret
	vector<Rochie> sortp();
	//inchiriaza
	void Inchiriere( string denu, string marime, int pret);


};