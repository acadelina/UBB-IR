#pragma once
#include "MyList.h"
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "medicamente.h"

medicament* creator(int cod, char* nume, int concentratie, int cantitate) {
	/* Vom crea o instanta de tip medicament */
	medicament* rez = malloc(sizeof(medicament));
	if (rez!=NULL)
	{
		int nrC = (int)strlen(nume) + 1;
		rez->nume = malloc(nrC * sizeof(char));
		strcpy_s(rez->nume, nrC, nume);
		rez->concentratie = concentratie;
		rez->cantitate = cantitate;
		rez->cod = cod;
		
	}
	return rez;
}
void destroyMed(medicament* m)
{
	free(m->nume);
	free(m);
}
medicament* copyMed(medicament* m) {
	return creator(m->cod, m->nume, m->concentratie,m->cantitate);
}
bool validareCod(medicament* pastila) {
	/* vom valida datele de intrare*/

	bool corect = true;
	if (pastila->cantitate < 0) {
		corect = false;
	}
	if (pastila->concentratie < 0 || pastila->concentratie>99) {
		corect = false;

	}

	if (pastila->cod < 0) {
		corect = false;

	}
	if (corect == false) return false;
	return true;
}

void testareValidare() {
	medicament* m1 = creator( 1,"Aspacardin",10,-10 );
	medicament* m2 = creator( 2,"Brufen",200,100 );
	medicament* m3 = creator( - 3, "Antrax", 50, 300 );
	medicament* m4 = creator( 3,"Antrax",50,300 );
	assert(validareCod(m1) == false);
	assert(validareCod(m2) == false);
	assert(validareCod(m3) == false);
	assert(validareCod(m4) == true);
	destroyMed(m1);
	destroyMed(m2);
	destroyMed(m3);
	destroyMed(m4);
}