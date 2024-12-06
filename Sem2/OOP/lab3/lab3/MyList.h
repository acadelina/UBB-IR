#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "prod.h"
typedef Produs ElemType;
typedef struct {
	ElemType* elems;
	int lg;
	int capacitate;
}MyList;

MyList creeazaVid();

void distruge(MyList* l);

ElemType get(MyList* l, int poz);

ElemType set(MyList* l, int poz, Produs p);

int size(MyList* l);

void add(MyList* l, ElemType el);

ElemType delete(MyList* l, int poz);

MyList copyList(MyList* l);

void testIterateList();