#pragma once
#define _CRTDBG_MAP_ALLOC
#include "MyList.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef struct
{/* ne definim tipul de daca medicament, cu caracteristicile sale*/
	int cod;
	char* nume;
	int concentratie;
	int cantitate;
}medicament;

/*
Creeaza un medicament
cod-int
nume-char
concentratie-int
antitate-int
*/
medicament* creator(int cod, char* nume, int concentratie, int cantitate);

/*
Distruge medicament
Elibereaza memoria alocata
m-medicament*
*/
void destroyMed(medicament* m);

/*
Copiaza medicament
creeaza un medicament identic cu cel dat
*/
medicament* copyMed(medicament* m);

/*
functie de validare a medicamentului
*/
bool validareCod(medicament* pastila);

void testareValidare();