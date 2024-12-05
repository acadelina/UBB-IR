#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4,4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1,1,5);
	assert(m.element(1,1) == 5);
	m.modifica(1,1,6);
	assert(m.element(1,2) == NULL_TELEMENT);
	m.modifica(1, 1, 0);
	assert(m.element(1, 1) == NULL_TELEMENT);
	m.modifica(1, 1, 0);
	assert(m.element(1, 1) == NULL_TELEMENT);

	Matrice m2(4, 4);
	m2.modifica(1, 1, 1);
	m2.modifica(1, 2, 2);
	m2.modifica(1, 3, 3);
	m2.modifica(2, 1, 4);
	m2.modifica(2, 2, 5);
	m2.modifica(2, 3, 6);
	Matrice tr = m2.transpusa();
	assert(tr.element(1, 1) == 1);
	assert(tr.element(2, 1) == 2);
	assert(tr.element(3, 1) == 3);
	assert(tr.element(1, 2) == 4);
	assert(tr.element(2, 2) == 5);
	assert(tr.element(3, 2) == 6);
	
}
