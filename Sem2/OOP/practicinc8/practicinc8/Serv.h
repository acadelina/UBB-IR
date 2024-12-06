#pragma once
#include"Repo.h"
#include<map>

class Serv
{
	Repo& rep;
public:
	Serv(Repo& rep) :rep{ rep } {};
	/*
	Functie care returneaza vectorul de melodii sortat dupa rank
	*/
	vector<Melodie> sort();
	/*
	Functie care returneaza un dictionar cu rankurile si numarul melodiilor cu respectivul rank
	*/
	map<int, int> rankuri();
	/*
	Functie care modifica o melodie
	prec:id-int
		 titlu-string
		 rank-int
	*/
	void modificare(int id, string titlu, int rank);
	/*
	Functie care sterge o melodie dupa id
	prec:id-int
	*/
	void sterge(int id);

	int art(string a);

};

void testServ();
