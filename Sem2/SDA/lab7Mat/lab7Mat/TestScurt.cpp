#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modifica(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEMENT);
}

void testEliminaAparitii()
{
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modifica(2, 2, 6);
	m.modifica(1, 2, 5);
	assert(m.element(1, 2) == 5);
	int nr = m.eliminaAparitii(5);
	assert(nr == 2);
	assert(m.element(1, 2) == NULL_TELEMENT);
	assert(m.element(1, 1) == NULL_TELEMENT);
	assert(m.eliminaAparitii(1) == 0);
}