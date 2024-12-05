#pragma once
#include "MyList.h"
#include "medicamente.h"

typedef struct {
	MyList* allMeds;
	MyList* undoList;
}ManagerMeds;

/*
Creaza o entitate de tip ManagerMeds care contine o
lista de medicamente si una pentru undo
*/
ManagerMeds createManagerMeds();

/*
* Elibereaza memoria alocata pentru un ManagerMelodii
*/
void destroyManagerMeds(ManagerMeds* store);


/*
* Adauga un med
*
* @param store: ManagerMeds in care se adauga (ManagerMeds*)
* @param cod: codul med care se adauga (char*)
* @param nume: numele med care se adauga (char*)
* @param concentratie: concentratia med care se adauga (float)
* @param stoc: stocul med care se adauga (int)
*
* @return: 1 daca med a fost adaugat cu succes, 0 altfel (int)
* post: med cu datele date este adaugat in lista (daca este valid)
*/
int adaugareService(ManagerMeds* store, int cod, char* nume, int concentratie, int cantitate);

/*
*Gaseste un med cu nume dat
*
* @param store : ManagerMeds in care se cauta (ManagerMeds*)
* @param cod : codul med care se cauta(char*)
*
* @return: pozitia din lista a med cautat, -1 daca
med nu exista in lista(int)
*/
int findMed(ManagerMeds* store, char* nume);

/*
* Modifica un med
*
* @param farmacie: ManagerMeds in care se modifica 
* @param cod: codul med care se modifica (char*)
* @param nume: numele med cu care se modifica (char*)
* @param concentratie: concentratia med cu care se modifica (float)
* @param stoc: stocul med care se modifica (int)
* @return: 1 daca med a fost modificat cu succes, 0 altfel (int)
* post:med cu codul cod are un nume si o concentratie noua (daca un astfel
*		de med exista)
*/
int modifyMed(ManagerMeds* store, int cod, char* nume, int concentratie, int cant);

/*
* Sterge stocul unui med
*
* @param farmacie: ManagerMeds din care se sterge ( ManagerMeds* )
* @param nume: numele med care se sterge (char*)
*
* post:med cu numele nume are stocul 0 daca exista
*/
void stergereService(ManagerMeds* store, char* nume);

void updateService(ManagerMeds* store, char* nume, char* numeNou, int concentratie);

/*
* Sterge un med
*
* @param farmacie: ManagerMeds din care se sterge ( ManagerMeds* )
* @param nume: numele med care se sterge (char*)
*
* @return: 1 daca med a fost sters cu succes, 0 altfel (int)
* post:med cu numele nume este sters din lista daca exista
*/
int deleteService(ManagerMeds* store, char* nume);




/*
Returneaza o lista cu med filtrate dupa cantitate

* @param store: ManagerMeds din care se sterge ( ManagerMeds* )
* @param number: numarul dupa care se filtreaza(int)
*
* @return: l(MyList*)

*/
MyList* filtrareCantitate(ManagerMeds* store, int number);



/*
Returneaza o lista cu med filtrate dupa litera cu care incepe numele

* @param store: ManagerMeds din care se sterge ( ManagerMeds* )
* @param caracter: caracterul dupa care se filtreaza(char)
*
* @return: l(MyList*)

*/
MyList* filtrareLitera(ManagerMeds* store, char caracter);



/*
Returneaza o lista cu med filtrate dupa concentratie

* @param store: ManagerMeds din care se sterge ( ManagerMeds* )
* @param con: numarul dupa care se filtreaza(int)
*
* @return: l(MyList*)

*/
MyList* filtrareConcentratie(ManagerMeds* store, int con);

/*
Functii de comparare in functie de un criteriu(nume/stoc) crescator sau descrescator
*/
int cmpStoc(medicament* m1, medicament* m2);

int cmpStocD(medicament* m1, medicament* m2);

int cmpNume(medicament* m1, medicament* m2);

int cmpNumeD(medicament* m1, medicament* m2);


/*
* Returneaza o lista sortata de medicamente
* Criteriu de sortare: stoc (crescator)
*
* @param farmacie: Farmacie cu medicamentele care se sorteaza (Farmacie*)
*
* @return: o lista sortata de medicamente  (MyList*)
*/

MyList* sortStoc(MyList* l,int m);


/*
* Returneaza o lista sortata de medicamente
* Criteriu de sortare: stoc (descrescator)
*
* @param farmacie: Farmacie cu medicamentele care se sorteaza (Farmacie*)
*
* @return: o lista sortata de medicamente  (MyList*)
*/

MyList* sortStocD(MyList* l,int m);

/*
* Returneaza o lista sortata de medicamente
* Criteriu de sortare: nume (crescator)
*
* @param farmacie: Farmacie cu medicamentele care se sorteaza (Farmacie*)
*
* @return: o lista sortata de medicamente  (MyList*)
*/

MyList* sortNume(MyList* l,int m);

/*
* Returneaza o lista sortata de medicamente
* Criteriu de sortare: nume (descrescator)
*
* @param farmacie: Farmacie cu medicamentele care se sorteaza (Farmacie*)
*
* @return: o lista sortata de medicamente  (MyList*)
*/
MyList* sortNumeD(MyList* l,int m);

/*
* Reface ultima operatie
*
* @return: 1 daca undo-ul a fost realizat, 0 altfel (int)
* post: lista de medicamente este cea aferenta efectuarii ultimei operatii care a modificat-o
*/
int undo(ManagerMeds* store);


void testSortStoc();
void testSortStocD();
void testSortNume();
void testSortNumeD();
void testCmpNumeD();
void testCmpStocD();
void testCmpNume();
void testFiltrareCaracter();
void testareStergere();
void testareUpdate();
void testareDelete();
void testareCantitate();
void testareAdaugare();
void testareConcentratie();
void testUndo();