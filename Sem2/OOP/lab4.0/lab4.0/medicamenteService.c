#include "MyList.h"
#include "medicamente.h"
#include "medicamenteService.h"
#include "customSort.h"
#include <assert.h>

ManagerMeds createManagerMeds()
{
	ManagerMeds store;
	store.allMeds = emptylist(destroyMed);
	store.undoList = emptylist(destroyList);
	return store;
}

void destroyManagerMeds(ManagerMeds* store)
{
	destroyList(store->allMeds);
	destroyList(store->undoList);
}
int adaugareService(ManagerMeds* store, int cod, char* nume, int concentratie, int cantitate) {

	medicament* pastila = creator(cod, nume, concentratie, cantitate);
	bool er = validareCod(pastila);
	if (!er)
	{
		destroyMed(pastila);
		return 0;
	}
	int poz = findMed(store, nume);
	MyList* toUndo = copyList(store->allMeds, copyMed);
	if (poz == -1)
	{
		adaugareRepo(store->allMeds, pastila);
	}
	else
	{
		medicament* m2 = get(store->allMeds, poz);
		cantitate = m2->cantitate + pastila->cantitate;
		modifyMed(store, cod, nume, concentratie, cantitate);
		destroyMed(pastila);
	}
	
	
	adaugareRepo(store->undoList, toUndo);

	return 1;
}

int findMed(ManagerMeds* store, char* nume) {

	int poz_to_delete = -1;

	for (int i = 0; i < store->allMeds->lenght; i++) {
		medicament* m = get(store->allMeds, i);
		if (strcmp(m->nume, nume) == 0 ) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}

int modifyMed(ManagerMeds* store, int cod, char* nume, int concentratie, int cant) {
	int poz = findMed(store, nume);

	if (poz != -1) {
		MyList* toUndo = copyList(store->allMeds, copyMed);
		adaugareRepo(store->undoList, toUndo);

		medicament* m2 = creator(cod, nume, concentratie, cant);
		medicament* m = get(store->allMeds, poz);
		destroyMed(m);
		setElem(store->allMeds, poz, m2);
		return 1;
	}
	
		return 0;
}

int deleteService(ManagerMeds* store, char* nume) {
	
	int poz = findMed(store, nume);
	if (poz != -1)
	{
		MyList* toUndo = copyList(store->allMeds, copyMed);
		adaugareRepo(store->undoList, toUndo);
		medicament* m = deleteRepo(store->allMeds, poz);
		destroyMed(m);
		return 1;
	}
	return 0;
}

void updateService(ManagerMeds* store, char* nume, char* numeNou,int concentratie) {
	int poz = findMed(store, nume);
	if (poz != -1)
	{
		MyList* toUndo = copyList(store->allMeds, copyMed);
		adaugareRepo(store->undoList, toUndo);
		medicament* m2 = get(store->allMeds, poz);
		medicament* m = creator(m2->cod,numeNou,concentratie,m2->cantitate);
		
		destroyMed(m2);
		setElem(store->allMeds, poz, m);
		
		
	}
	
}

void stergereService(ManagerMeds* store, char* nume) {
	
	int poz = findMed(store, nume);
	if (poz != -1)
	{
		MyList* toUndo = copyList(store->allMeds, copyMed);
		adaugareRepo(store->undoList, toUndo);
		medicament* m2 = get(store->allMeds, poz);
		medicament* m = creator(m2->cod, m2->nume, m2->concentratie, 0);

		destroyMed(m2);
		setElem(store->allMeds, poz, m);
		

	}

}
/*void schimbMedicamente(medicament* pastila1, medicament* pastila2) {
	int clonaConcentratie = pastila1->concentratie;
	int clonaCantitate = pastila1->cantitate;
	int clonaCod = pastila1->cod;
	char clonaNume[30];
	strcpy_s(clonaNume, sizeof(pastila1->nume), pastila1->nume);
	pastila1->concentratie = pastila2->concentratie;
	pastila1->cod = pastila2->cod;
	pastila1->cantitate = pastila2->cantitate;
	strcpy_s(pastila1->nume, sizeof(pastila2->nume), pastila2->nume);
	pastila2->cod = clonaCod;
	pastila2->cantitate = clonaCantitate;
	pastila2->concentratie = clonaConcentratie;
	strcpy_s(pastila2->nume, sizeof(clonaNume), clonaNume);

}

void filtrareCrescDesc(ManagerMeds* store, char* tip) {
	if (strcmp(tip, "crescator") == 0) {
		for (int i = 0; i < store->allMeds->lenght - 1; i++) {
			for (int j = i + 1; j < store->allMeds->lenght; j++)
			{
				medicament* m1 = store->allMeds->lista[i];
				medicament* m2 = store->allMeds->lista[j];
				if (strcmp(m1->nume, m2->nume) > 0)
					schimbMedicamente(m1, m2);
				else if (strcmp(m1->nume,m2->nume) == 0) {
					if (m1->cantitate > m2->cantitate)
						schimbMedicamente(m1, m2);


				}
				
			}
		}
	}
	else if (strcmp(tip, "descrescator") == 0) {
		for (int i = 0; i < store->allMeds->lenght - 1; i++) {
			for (int j = i + 1; j < store->allMeds->lenght; j++)
			{
				medicament* m1 = store->allMeds->lista[i];
				medicament* m2 = store->allMeds->lista[j];
				if (strcmp(m1->nume, m2->nume) < 0)
					schimbMedicamente(m1, m2);
				else if (strcmp(m1->nume, m2->nume) == 0) {
					if (m1->cantitate < m2->cantitate)
						schimbMedicamente(m1, m2);
				}
			}
		}
	}
*/
MyList* filtrareCantitate(ManagerMeds* store, int number) {
	MyList* copie = emptylist(destroyMed);
	for (int i = 0; i < store->allMeds->lenght; i++) {
		medicament* m = store->allMeds->lista[i];
		if (m->cantitate < number)
			adaugareRepo(copie, copyMed(m));

	}
	return copie;

}
MyList* filtrareLitera(ManagerMeds* store, char caracter) {
	MyList* copie = emptylist(destroyMed);
	for (int i = 0; i < store->allMeds->lenght; i++) {
		medicament* m = store->allMeds->lista[i];
		if (m->nume[0] == caracter)
			adaugareRepo(copie, copyMed(m));
	}
	return copie;

}

MyList* filtrareConcentratie(ManagerMeds* store, int con) {
	MyList* copie = emptylist(destroyMed);
	for (int i = 0; i < store->allMeds->lenght; i++) {
		medicament* m = store->allMeds->lista[i];
		if (m->concentratie == con)
			adaugareRepo(copie, copyMed(m));

	}
	return copie;

}
/*
void testSchimbare() {
	medicament* m1 = creator( 1, "Aspacardin", 100, 20 );
	medicament* m2 = creator( 2, "Aspacardin2", 1000, 200 );
	schimbMedicamente(m1, m2);
	assert(m1->cod == 2);
	assert(m1->cantitate == 200);
	assert(m1->concentratie == 1000);
	assert(strcmp(m1->nume, "Aspacardin2") == 0);
	assert(m2->cod == 1);
	assert(m2->cantitate == 20);
	assert(m2->concentratie == 100);
	assert(strcmp(m2->nume, "Aspacardin") == 0);
	destroyMed(m1);
	destroyMed(m2);
}

void testFiltrare() {
	ManagerMeds m = createManagerMeds();
	
	adaugareService(&m, 10, "Nurofen", 10, 20);
	adaugareService(&m, 10, "Aspacardin", 100, 2000);
	adaugareService(&m, 20, "Aspacardin", 10, 30);
	filtrareCrescDesc(&m, "crescator");
	medicament* med = m.allMeds->lista[0];
	medicament* med2 = m.allMeds->lista[1];
	assert(strcmp(med->nume, "Aspacardin") == 0);
	assert(med->cantitate == 30);
	assert(strcmp(med2->nume, "Aspacardin") == 0);
	assert(med2->cantitate == 2000);
	
	
	
	filtrareCrescDesc(&m, "descrescator");
	med= m.allMeds->lista[0];
	med2 = m.allMeds->lista[1];
	medicament* med3 = m.allMeds->lista[2];
	assert(strcmp(med3->nume, "Aspacardin") == 0);
	assert(med3->cantitate == 30);
	assert(strcmp(med2->nume, "Aspacardin") == 0);
	assert(med2->cantitate == 2000);
	assert(strcmp(med->nume, "Nurofen") == 0);
	destroyManagerMeds(&m);
}*/

/*void copiere(MyList* destinatie, MyList* sursa) {
	destinatie->lenght = sursa->lenght;
	for (int i = 0; i < destinatie->lenght; i++) {
		destinatie->lista[i].cod = sursa->lista[i].cod;
		destinatie->lista[i].cantitate = sursa->lista[i].cantitate;
		destinatie->lista[i].concentratie = sursa->lista[i].concentratie;
		strcpy_s(destinatie->lista[i].nume, sizeof(sursa->lista[i].nume), sursa->lista[i].nume);
	}

}

	void testareCopiere() {
	MyList sursa = emptylist();
	MyList destinatie = emptylist();
	medicament m1 = { 1,"Aspacardin",10,200 };
	medicament m2 = { 2,"Brufen",20,100 };
	adaugareRepo(&sursa, m1);
	adaugareRepo(&sursa, m2);
	copiere(&destinatie, &sursa);
	assert(destinatie.lenght == 2);
	assert(strcmp(destinatie.lista[0].nume, "Aspacardin") == 0);
	assert(strcmp(destinatie.lista[1].nume, "Brufen") == 0);
	destroyList(&sursa);
	destroyList(&destinatie);


}*/

void testareAdaugare()
{
	ManagerMeds m = createManagerMeds();
	assert(adaugareService(&m, -1, "aa", 10, 10) == 0);
	assert(adaugareService(&m, 1, "aa", 10, 10) == 1);
	assert(adaugareService(&m, 1, "aa", 10, 10) == 1);
	destroyManagerMeds(&m);

}
void testareCantitate() {
	ManagerMeds m = createManagerMeds();
	MyList* destinatie;
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	destinatie=filtrareCantitate(&m, 190);
	assert(destinatie->lenght == 1);
	medicament* med = destinatie->lista[0];
	assert(strcmp(med->nume, "Brufen") == 0);
	destroyManagerMeds(&m);
	destroyList(destinatie);


}

void testareConcentratie() {
	ManagerMeds m = createManagerMeds();
	MyList* destinatie;
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	destinatie = filtrareConcentratie(&m, 20);
	assert(destinatie->lenght == 1);
	medicament* med = destinatie->lista[0];
	assert(strcmp(med->nume, "Brufen") == 0);
	destroyManagerMeds(&m);
	destroyList(destinatie);


}

void testFiltrareCaracter() {
	ManagerMeds m = createManagerMeds();
	MyList* destinatie ;
	
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	destinatie=filtrareLitera(&m, 'A');
	assert(destinatie->lenght == 2);

	medicament* med = destinatie->lista[0];
	medicament* med1 = destinatie->lista[1];
	assert(strcmp(med->nume, "Aspacardin") == 0);
	assert(strcmp(med1->nume, "Antrax") == 0);
	destroyManagerMeds(&m);
	destroyList(destinatie);
}

void testareStergere() {
	ManagerMeds m = createManagerMeds();

	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	stergereService(&m, "Antrax");

	medicament* med = m.allMeds->lista[2];
	assert(med->cantitate == 0);
	destroyManagerMeds(&m);

}
void testareDelete() {
	ManagerMeds m = createManagerMeds();

	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	deleteService(&m, "Brufen");
	assert(m.allMeds->lenght == 2);
	medicament* med = m.allMeds->lista[0];
	medicament* med1 = m.allMeds->lista[1];
	assert(strcmp(med->nume, "Aspacardin") == 0);
	assert(strcmp(med1->nume, "Antrax") == 0);
	deleteService(&m, "a");
	destroyManagerMeds(&m);
}

void testareUpdate() {
	ManagerMeds m = createManagerMeds();

	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	updateService(&m, "Brufen", "Nurofen", 30);
	medicament* med1 = m.allMeds->lista[1];
	assert(strcmp(med1->nume, "Nurofen") == 0);
	assert(med1->concentratie == 30);
	assert(modifyMed(&m,1, "aa", 11, 10) == 0);
	destroyManagerMeds(&m);
	
}
int cmpStoc(medicament* m1, medicament* m2) {
	if (m1->cantitate == m2->cantitate)
		return 0;
	if (m1->cantitate > m2->cantitate)
		return 1;
	else
		return -1;
}

int cmpStocD(medicament* m1, medicament* m2) {
	if (m1->cantitate == m2->cantitate)
		return 0;
	if (m1->cantitate < m2->cantitate)
		return 1;
	else
		return -1;
}

int cmpNume(medicament* m1, medicament* m2) {
	return strcmp(m1->nume, m2->nume);
}

int cmpNumeD(medicament* m1, medicament* m2) {
	if (strcmp(m1->nume, m2->nume) > 0)
		return -1;
	if (strcmp(m1->nume, m2->nume) < 0)
		return 1;
	else
		return 0;
}

MyList* sortStoc(MyList* l,int m) {
	if (m == 0)
	{
		sort(l, cmpStoc);
	}
	else
	{
		insertSort(l, cmpStoc);
	}
	return l;
}

MyList* sortStocD(MyList* l,int m) {
	if (m == 0)
	{
		sort(l, cmpStocD);
	}
	else
	{
		insertSort(l, cmpStocD);
	}
	return l;
}

MyList* sortNume(MyList* l,int m) {
	if (m == 0)
	{
		sort(l, cmpNume);
	}
	else
	{
		insertSort(l, cmpNume);
	}
	return l;
}
MyList* sortNumeD(MyList* l,int m) {
	if (m == 0)
	{
		sort(l, cmpNumeD);
	}
	else
	{
		insertSort(l, cmpNumeD);
	}
	return l;
}

int undo(ManagerMeds* store) {
	if (store->undoList->lenght== 0)
		//nothing to undo
		return 0;
	MyList* v = deleteRepo(store->undoList, store->undoList->lenght - 1);
	destroyList(store->allMeds);
	store->allMeds = v;
	return 1;
}

void testSortStoc() {
	ManagerMeds m = createManagerMeds();
	// Add some medicament objects to the list
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	// Perform sorting
	MyList* sortedList = sortStoc(m.allMeds,1);
	sortStoc(m.allMeds, 0);
	medicament* a = get(sortedList, 0);
	assert(a->cantitate == 100);
	// Assert statements to check if sorting is correct
	
	
	destroyManagerMeds(&m);
	//destroyList(sortedList);
}

void testSortStocD() {
	ManagerMeds m = createManagerMeds();
	// Add some medicament objects to the list
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);
	MyList* sortedList = sortStocD(m.allMeds,0);
	sortedList = sortStocD(m.allMeds, 1);
	// Assert statements to check if sorting is correct
	for (int i = 0; i < sortedList->lenght - 1; i++) {
		assert(cmpStocD((sortedList->lista[i]), (sortedList->lista[i + 1])) <= 0);
	}

	// Cleanup
	destroyManagerMeds(&m);
	//destroyList(sortedList);
}


void testSortNume() {
	// Create a list and add some medicament objects to it
	ManagerMeds m = createManagerMeds();
	// Add some medicament objects to the list
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);

	// Perform sorting
	sortNume(m.allMeds,0);
	sortNume(m.allMeds, 1);

	// Assert statements to check if sorting is correct
	for (int i = 0; i < m.allMeds->lenght - 1; i++) {
		assert(cmpNume((m.allMeds->lista[i]), (m.allMeds->lista[i + 1])) <= 0);
	}

	// Cleanup
	destroyManagerMeds(&m);
}

void testSortNumeD() {
	ManagerMeds m = createManagerMeds();
	// Add some medicament objects to the list
	adaugareService(&m, 1, "Aspacardin", 10, 200);
	adaugareService(&m, 2, "Brufen", 20, 100);
	adaugareService(&m, 3, "Antrax", 50, 300);

	// Perform sorting
	MyList* sortedList = sortNumeD(m.allMeds, 1);
	sortedList = sortNumeD(m.allMeds, 0);

	// Assert statements to check if sorting is correct
	for (int i = 0; i < sortedList->lenght - 1; i++) {
		assert(cmpNumeD((sortedList->lista[i]), (sortedList->lista[i + 1])) <= 0);
	}

	// Cleanup
	//destroyList(sortedList);
	destroyManagerMeds(&m);
}


void testCmpStocD() {
	medicament m1 = { 1,"Aspacardin",10,200 };
	medicament m2 = { 2,"Brufen",20,100 };
	medicament m3 = { 3,"a",20,100 };

	// Test cases
	assert(cmpStocD(&m1, &m2) == -1); // m1 should be greater than m2
	assert(cmpStocD(&m2, &m1) == 1); // m2 should be less than m1
	assert(cmpStocD(&m2, &m3) == 0);
	assert(cmpStoc(&m2, &m3) == 0);


}

// Test case for cmpNume function
void testCmpNume() {
	// Create sample medicaments
	medicament m1 = { 1,"Aspacardin",10,200 };
	medicament m2 = { 2,"Brufen",20,100 };

	// Test cases
	assert(cmpNume(&m1, &m2) < 0); // m1 should be less than m2
	assert(cmpNume(&m2, &m1) > 0); // m2 should be greater than m1

}

// Test case for cmpNumeD function
void testCmpNumeD() {
	// Create sample medicaments
	medicament m1 = { 1,"Aspacardin",10,200 };
	medicament m2 = { 2,"Brufen",20,100 };
	medicament m3 = { 3,"Brufen",90,11 };

	// Test cases
	assert(cmpNumeD(&m1, &m2) > 0); // m1 should be greater than m2
	assert(cmpNumeD(&m2, &m1) < 0); // m2 should be less than m1
	assert(cmpNumeD(&m2, &m3) == 0);


}

void testUndo() {
	ManagerMeds farmacie = createManagerMeds();
	adaugareService(&farmacie, 1, "Aspacardin", 10, 200);
	deleteService(&farmacie, "Aspacardin");

	undo(&farmacie);
	
	assert(farmacie.allMeds->lenght == 1);
	medicament* m = get(farmacie.allMeds, 0);
	assert(m->concentratie == 10);
	

	undo(&farmacie);
	
	assert(farmacie.allMeds->lenght == 0);
	

	
	destroyManagerMeds(&farmacie);
}