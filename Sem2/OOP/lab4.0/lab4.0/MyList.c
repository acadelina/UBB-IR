#include "MyList.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "medicamente.h"
#include "medicamenteService.h"
#include <stdlib.h>

MyList* emptylist(DestroyFct f) {
	MyList* list=malloc(sizeof(MyList));
	if (list)
	{
		list->lenght = 0;
		list->capacitate = 5;
		list->lista = malloc(list->capacitate * sizeof(medicament));
		list->dfnc = f;
		
	}
	return list;
}


MyList* copyList(MyList* v, CopyFct copyFct) {
	MyList* v_copy = emptylist(v->dfnc);
	for (int i = 0; i < v->lenght; i++) {
		ElemType el = get(v, i);
		adaugareRepo(v_copy, copyFct(el));
	}
	return v_copy;
}

void destroyList(MyList* l) {
	for (int i = 0; i < l->lenght; i++)
		l->dfnc(l->lista[i]);
	
	l->lenght = 0;
	free(l->lista);
	free(l);
}


void adaugareRepo(MyList* list, ElemType m) {
	/* adauga si modifica lungimea*/
	if (list->lenght >= list->capacitate) {
		int newCap = list->capacitate * 2;
		ElemType* aux_elems = malloc(sizeof(medicament) * newCap);
		for (int i = 0; i < list->lenght; i++) {
			aux_elems[i] = list->lista[i];
		}
		free(list->lista);
		list->lista = aux_elems;
		list->capacitate = newCap;
	}
	list->lista[list->lenght] = m;
	list->lenght++;


}


ElemType get(MyList* v, int poz) {
	return (medicament*)v->lista[poz];
}

ElemType setElem(MyList* v, int poz, ElemType el) {
	ElemType replaced = v->lista[poz];
	v->lista[poz] = el;
	return replaced;
}



void updateRepo(MyList* list, medicament* pastila, char* numeNou) 
{	/*cautam daca medicamentul se afla in baza de date si apoi modificam concentratia daca il gasim*/
	
		for (int i = 0; i < list->lenght; i++)
		{
			medicament* m1 = list->lista[i];

			if (strcmp(m1->nume, pastila->nume) == 0) {
				strcpy_s(m1->nume, sizeof(m1->nume), numeNou);
				m1->concentratie = pastila->concentratie;
				
			}
		}
}


/*int verificaExistenta(MyList* l, medicament* meds) {
	verificam in vector 
	for (int i = 0; i < l->lenght; i++) {
		medicament* l2 = get(l, i);
		if (strcmp(l2->nume, meds->nume) == 0)
			return i;
	}
	return -1;

}*/
ElemType deleteRepo(MyList* l, int poz) {
	ElemType el = l->lista[poz];
		for (int j = poz; j < l->lenght - 1; j++) {
			l->lista[j] = l->lista[j + 1];
		}

		// Decrement the length of the list
		l->lenght--;
		return el;
}


void test_emptylist() {
	// Test  empty list
	MyList* list = emptylist(destroyMed);
	assert(list->lenght == 0);
	destroyList(list);
}

/*void testareExistenta() {
	MyList* sursa = emptylist(destroyMed);
	medicament* m1 =creator(1,"Aspacardin",10,200 );
	medicament* m2 = creator(2,"Brufen",20,100 );
	medicament* m3 = creator(3,"Antrax",50,300 );
	adaugareRepo(sursa, m1);
	adaugareRepo(sursa, m2);
	//assert(verificaExistenta(sursa, m1) == 0);
	//assert(verificaExistenta(sursa, m3) == -1);
	destroyList(sursa);
	destroyMed(m1);
	destroyMed(m2);
	destroyMed(m3);
}*/
void testAddRepo() {
	MyList* sursa = emptylist(destroyMed);
	medicament* m1 = creator( 1,"Aspacardin",10,200 );
	medicament* m2 = creator( 2,"Brufen",20,100 );
	medicament* m3 = creator( 2,"Brufen",20,100 );
	medicament* m4 = creator( 2,"Brufen",20,100 );
	medicament* m5 = creator(2,"Brufen",20,100 );
	medicament* m6 = creator( 2,"Brufen",20,100 );
	adaugareRepo(sursa, m1);
	adaugareRepo(sursa, m3);
	adaugareRepo(sursa, m2);
	adaugareRepo(sursa, m4);
	adaugareRepo(sursa, m5);
	adaugareRepo(sursa, m6);
	assert(sursa->lenght == 6);
	destroyList(sursa);
}

void testupdateRepo()
{
	MyList* sursa = emptylist(destroyMed);
	medicament* m1 = creator(1, "Aspacardin", 10, 200);
	
	adaugareRepo(sursa, m1);
	
	updateRepo(sursa, m1, "A");
	assert(strcmp(m1->nume, "A") == 0);
	destroyList(sursa);

}