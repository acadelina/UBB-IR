#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include"prod.h"
#include "MyList.h"


/*
Creeaza un manager de melodii
return-> managerul creat
*/
typedef struct {
	MyList allPr;
}Magazin;

Magazin creeazaMagazin();

int adaugarePr(MyList* l, int id, char* tip, char* prod, char* model, int pret, int cant);

int updatePret(MyList* l, int id, int pret);

int updateCant(MyList* l, int id, int cant);

int findPr(MyList* l, int id);

int sterge(MyList* l, int id);

MyList filtrPr(MyList* l, char* prod);

MyList filtrPret(MyList* l, int pret);

MyList filtrCant(MyList* l, int cant);

void swap(Produs* a, Produs* b);

void sortare(MyList* l, int ord);

void testAdd();


