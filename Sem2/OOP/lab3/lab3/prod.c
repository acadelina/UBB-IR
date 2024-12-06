#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#pragma once
#include "prod.h"
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include"MyList.h"

Produs creeazaPr(int id, char* tip, char* prod, char* model, int pret, int cant)
{
	Produs rez;
	rez.id = id;
	
	rez.cantitate = cant;
	rez.pret = pret;
	int nr = (int)strlen(tip) + 1;
	rez.tip = malloc(nr * sizeof(char));
	strcpy_s(rez.tip, nr, tip);

	 nr = (int)strlen(prod) + 1;
	rez.producator = malloc(nr * sizeof(char));
	strcpy_s(rez.producator, nr, prod);

	 nr = (int)strlen(model) + 1;
	rez.model = malloc(nr * sizeof(char));
	strcpy_s(rez.model, nr, model);

	
	return rez;

}

void distrugePr(Produs* p)
{
	p->cantitate = -1;
	p->id = -1;
	free(p->model);
	p->pret = -1;
	free(p->producator);
	free(p->tip);
	free(p);
}
Produs CopyPr(Produs* p)
{
	return creeazaPr(p->id, p->tip, p->producator, p->model, p->pret, p->cantitate);
	
}
int getPret(Produs* p)
{
	return p->pret;
}
int getCant(Produs* p)
{
	return p->cantitate;
}
char* getTip(Produs* p)
{
	return p->tip;
}
char* getProd(Produs* p)
{
	return p->producator;
}
char* getModel(Produs* p)
{
	return p->model;
}
int getId(Produs* p)
{
	return p->id;
}
int valideaza(Produs p)
{
	char* tipuri[4] = { "laptop", "frigider", "televizor", "altceva" };

	int ok = 0;
	for (int i = 0; i < 4; i++)
	{

		if (strcmp(tipuri[i], p.tip) == 0)
			ok = 1;
	}
	if (!ok)
		return 1;

	if (p.pret <= 0)
	{
		return 2;


	}
	if (p.cantitate <= 0)
	{
		return 3;


	}
	return 0;

}

void testCreateDestroy()
{
	Produs p = creeazaPr(1, "te", "p1", "m1", 100, 10);
	assert(p.id == 1);
	assert(strcmp(p.tip, "te") == 0);
	assert(strcmp(p.model, "m1") == 0);
}