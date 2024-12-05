#pragma once
#define _CRTDBG_MAP_ALLOC
#include "MyList.h"
#include<assert.h>
#include<string.h>
#include<stdlib.h>
MyList creeazaVid()
{
	MyList rez;
	rez.capacitate = 1;
	rez.elems = malloc(sizeof(ElemType) * rez.capacitate);
	rez.lg = 0;
	return rez;
}

void distruge(MyList* l)
{
	for (int i = 0; i < l->lg; i++)
	{
		ElemType p = get(l,i);
		distrugePr(&p);
	}
	free(l->elems);
	l->elems = NULL;
	l->lg = 0;
	
}

ElemType get(MyList* l, int poz)
{
	return l->elems[poz];
}
ElemType set(MyList* l, int poz, Produs p)
{
	ElemType rez = l->elems[poz];
	l->elems[poz] = p;
	return rez;
}
int size(MyList* l)
{
	return l->lg;
}

void add(MyList* l, ElemType el)
{
	if (l->capacitate <= l->lg)
	{
		ElemType* aux = malloc((l->capacitate + 5) * sizeof(Produs));
		for (int i = 0; i < l->lg; i++)
		{
			aux[i] = l->elems[i];
		}
		free(l->elems);
		l->elems = aux;
		l->capacitate = l->capacitate + 5;
	}
	l->elems[l->lg] = el;
	l->lg++;
}

ElemType delete(MyList* l, int poz)
{
	ElemType el = l->elems[poz];
	for (int i = poz; i < l->lg - 1; i++)
		l->elems[i] = l->elems[i + 1];
	l->lg--;
	return el;
}

MyList copyList(MyList* l)
{
	MyList rez = creeazaVid();
	for (int i = 0; i < size(l); i++)
	{
		ElemType p = get(l, i);
		add(&rez, p);
	}
	return rez;
}

void testCreateList() {
	MyList l = creeazaVid();
	assert(size(&l) == 0);
}
void testIterateList() {
	MyList l = creeazaVid();
	add(&l, creeazaPr(1, "televizor", "tip1", "v5000", 1000, 200));
	add(&l, creeazaPr(2, "televizor", "tip2", "v2000", 2000, 200));
	assert(size(&l) == 2);
	Produs p = get(&l, 0);

	assert(strcmp(p.tip, "televizor") == 0);
	p = get(&l, 1);
	assert(strcmp(p.producator, "tip2") == 0);
	distruge(&l);
	assert(size(&l) == 0);
}
