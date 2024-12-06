#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "medicamente.h"


typedef void* ElemType;

typedef void (*DestroyFct)(ElemType);

typedef ElemType(*CopyFct)(ElemType);

typedef struct {
	ElemType* lista;
	int lenght;
	int capacitate;
	DestroyFct dfnc;
} MyList;

/* Creare lista goala. */
MyList* emptylist(DestroyFct f);

/* Setare element. */
ElemType setElem(MyList* v, int poz, ElemType el);

/* Extragere element din lista. */
ElemType get(MyList* v, int poz);

/* Distrugere lista. */
void destroyList(MyList* l);

/* Adaugare element la lista. */
void adaugareRepo(MyList* lista, ElemType m);

/*Copie lista.*/
MyList* copyList(MyList* v, CopyFct copyFct);



/*Modificare element*/
void updateRepo(MyList* list, medicament* pastila, char* numeNou);

/*Stergere element*/
ElemType deleteRepo(MyList* l, int poz);

void test_emptylist();
//void testFiltrare();
//void testareExistenta();
void testAddRepo();

void testupdateRepo();
