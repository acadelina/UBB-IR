#pragma once
#include"produs.h"

//printare meniu comenzi
void printMeniu();

//printare lista de produse
void printList(Prlist* l);

//citirea datelor unui produs si adaugarea acestuia in lista
void addPrUi(Prlist* l);

//citirea datelor pentru modificare si efectuarea modificarii
void uiModif(Prlist* m);

//citirea datelor pentru filtrare si afisarea produselor filtrate
void uiFiltr(Prlist* m);

//citirea datelor pentru stergere si efectuarea stergerii
void uiSterge(Prlist* m);

//citirea datelor pentru sortare si efectuarea sortarii
void uiSort(Prlist* m);

//testare
void teste();

//functia principala
void run();
