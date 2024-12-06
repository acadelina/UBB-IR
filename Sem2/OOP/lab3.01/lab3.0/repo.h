#pragma once
#include"produs.h"

/*
	Functie care creeaza o structura lista vida
	preconditii:
	postcondiii: rez->Lista
*/
Prlist creeazaVid();


/*
	Functie care elibereaza spatiul alocat pentru o lista
*/
void destroy(Prlist* l);


/*
	Functie care creeaza un produs
	precond:id->int
			tip->char
			prod->char
			model->char
			pret->int
			cant->int
	postcond:rez->Produs
	*/
produs creeazaPr(int id, char tip[], char prod[], char model[], int pret, int cant);

int findPr(Prlist* l, int id);

/*
	Functie care adauga un produs
	precond:l->Lista
			p->produs
	postcond:
*/
void addPr(Prlist* l, produs p);

/*
Functie care sterge produsul de pe pozitia poz din lista
precond: l->lista
		 poz->int
postcond:
*/
void delPr(Prlist* l, int poz);

//functie de test pt repo

void testRepo();