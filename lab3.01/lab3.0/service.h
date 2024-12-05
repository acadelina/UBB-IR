#pragma once
#include"repo.h"

/*
	Functie care adauga un produs sau creste stocul daca acesta exista deja
	precond:l->Lista
			id->int
			tip->char
			prod->char
			model->char
			pret->int
			cant->int
	postcond:
	*/
int adaugaPr(Prlist* l, int id, char tip[], char prod[], char model[], int pret, int cant);

/*
	Functie care schimba pretul unui produs
	precond: l->Lista
			 id->int
			 pret->int
	postcond:1/0 daca produsul exista sau nu
	*/
int updatePret(Prlist* l, int id, int pret);

/*
	Functie care schimba cantitatea unui produs
	precond: l->Lista
			 id->int
			 cant->int
	postcond:1/0 daca produsul exista sau nu
	*/
int updateCant(Prlist* l, int id, int cant);

/*
	Functie care sterge un produs dupa id
	precond:l->Lista
			id->int
	postcond:1/0 daca produsul exista sau nu
	*/
int sterge(Prlist* l, int id);

/*
	Functie care creeaza o lista cu produsele ce au producatorul dat
	precond: l->Lista
			 prod->char
	postcond: nou->Lista
	*/
Prlist filtrPr(Prlist* l, char* prod);

/*
	Functie care creeaza o lista cu produsele ce au pretul dat
	precond: l->Lista
			 pret->int
	postcond: nou->Lista
	*/
Prlist filtrPret(Prlist* l, int pret);

/*
	Functie care creeaza o lista cu produsele ce au cantitatea data
	precond: l->Lista
			 cant->int
	postcond: nou->Lista
	*/
Prlist filtrCant(Prlist* l, int cant);

/*
	Functie de interschimbare a doua produse
	precond: a,b->Produs
	postcond:
	*/
int cmpModelAsc(const produs* p1, const produs* p2);

int cmpModelDesc(const produs* p1, const produs* p2);

/*
	Functie de sortare
	prcond:l->Lista
		   ord->int
	postcond:
	*/
void bsort(produs* p, int lg, int(*func)(produs* p1, produs* p2));

Prlist* sortare(Prlist* l, int ord);

void testServ();