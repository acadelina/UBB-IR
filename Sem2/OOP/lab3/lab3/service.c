#pragma once
#define _CRTDBG_MAP_ALLOC
#include"prod.h"
#include "service.h"

#include<stdlib.h>
#include<string.h>
#include<assert.h>

/*ManagerPr createManager()
{
	ManagerPr manager;
	manager.listaPr = creeazaVid();
	return manager;
}

void distrugeMan(ManagerPr* manager) {
	distruge(&manager->listaPr);
}*/
Magazin creeazaMagazin()
{
	Magazin rez;
	rez.allPr = creeazaVid();
	return rez;
}
void distrMAg(Magazin* m)
{
	distrue(&m->allPr);
}
int adaugarePr(Magazin* l, int id, char* tip, char* prod, char* model, int pret, int cant)
{
	Produs p = creeazaPr(id, tip, prod, model, pret, cant);
	int er = valideaza(p);
	if (er != 0)
	{
		distrugePr(&p);
		return er;
	}
	add(&l->allPr, p);
	return 0;
}

int updatePret(MyList* l, int id, int pret)
{
	int ok = 0;
	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l,i);
		if (p.id == id)
		{
			p.pret = pret;
			l->elems[i] = p;
			ok = 1;

		}

	}
	return ok;
}


int updateCant(MyList* l, int id, int cant)
{
	int ok = 0;

	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l, i);

		if (p.id == id)
		{

			p.cantitate = cant;
			l->elems[i] = p;
			ok = 1;

		}

	}
	return ok;

}
int findPr(MyList* l, int id)
{
	int poz_del = -1;
	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l, i);
		if (id == p.id)
		{
			poz_del = i;
			break;
		}
	}
	return poz_del;
}
int sterge(MyList* l, int id)
{
	int poz_del = findPr(l, id);
	if (poz_del != -1)
	{
		Produs p = delete(l, poz_del);
		distrugePr(&p);
		return 1;
	}
	return 0;
}

MyList filtrPr(MyList* l, char* prod)
{
	MyList nou = creeazaVid();
	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l, i);
		if (strcmp(p.producator, prod) == 0)
		{
			add(&nou, p);
		}
	}
	return nou;
}

MyList filtrPret(MyList* l, int pret)
{
	MyList nou = creeazaVid();
	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l, i);
		if (p.pret== pret)
		{
			add(&nou, p);
		}
	}
	return nou;
}

MyList filtrCant(MyList* l, int cant)
{
	MyList nou = creeazaVid();
	for (int i = 0; i < size(l); i++)
	{
		Produs p = get(l, i);
		if (p.cantitate == cant)
		{
			add(&nou, p);
		}
	}
	return nou;
}

void swap(Produs* a, Produs* b)
{
	
	Produs aux = *a;
	*a = *b;
	*b = aux;

}

void sortare(MyList* l, int ord)
{
	
	int i, j, ok;
	if (ord == 0)
	{
		for (i = 0; i < size(l); i++)
		{
			ok = 0;
			for (j = 0; j < size(l) - 1; j++)
			{
				if (((get(l,j).pret > (get(l, j+1)).pret) || ((get(l, j)).pret == (get(l, j+1)).pret && (get(l, j)).cantitate > (get(l, j+1)).cantitate)))
				{
					swap(&(l->elems[j]), &(l->elems[j+1]));
					ok = 1;
				}
			}
			if (ok == 0)
				break;
		}
	}
	else
	{
		for (i = 0; i < size(l); i++)
		{
			ok = 0;
			for (j = 0; j < size(l) - 1; j++)
			{
				if (((get(l, j).pret < (get(l, j + 1)).pret) || ((get(l, j)).pret == (get(l, j + 1)).pret && (get(l, j)).cantitate < (get(l, j + 1)).cantitate)))
				{
					swap(&(l->elems[j]), &(l->elems[j + 1]));
					ok = 1;
				}
			}
			if (ok == 0)
				break;
		}
	}
}

void testAdd()
{
	MyList l = creeazaVid();

	int er = adaugarePr(&l, 1, "te", "p1", "m1", 100, 10);
	assert(er == 1);
	assert(size(&l) == 0);

}