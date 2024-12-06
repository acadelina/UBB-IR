//#define _CRT_SECURE_NO_WARNINGS
#include "produs.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>

Prlist creeazaVid()
{
	Prlist l;
	
	
		
		l.lg = 0;
		l.cap = 10;
		l.produse = malloc(sizeof(produs) * l.cap);
	
	return l;

}


void destroy(Prlist* l)
{
	
	free(l->produse);
	
	
}

produs creeazaPr(int id, char tip[], char prod[], char model[], int pret, int cant)
{
	produs rez;
	rez.id = id;
	rez.cantitate = cant;
	rez.pret = pret;
	strcpy(rez.tip, tip);
	strcpy(rez.producator, prod);
	strcpy(rez.model, model);


	return rez;

}

int findPr(Prlist* l, int id)
{
	for (int i = 0; i < l->lg; i++)
		if (l->produse[i].id == id)
			return i;
	return -1;
}

void addPr(Prlist* l, produs p)
{
	if (l->lg < l->cap)
	{
		l->produse[l->lg] = p;
		l->lg++;
	}
	else
	{
		int newcap = l->cap * 2;
		produs* np = realloc(l->produse, newcap * sizeof(produs));
		if (np != NULL && l->produse != NULL)
		{
			l->produse = np;
			l->cap = newcap;
			l->produse[l->lg] = p;
			l->lg++;
		}
	}
}




void delPr(Prlist* l, int poz)
{
	for (int i = poz; i < l->lg; i++)
		l->produse[i] = l->produse[i + 1];
	l->lg--;
	
}

void testRepo()
{
	Prlist lt = creeazaVid();
	Prlist *l = &lt;
	assert(l->lg == 0);
	assert(l->cap == 10);

	//assert(creeazaVid())

	produs p = creeazaPr(1, "televizor", "tip1", "v5000", 1000, 200);
	assert(p.id == 1);
	assert(p.pret == 1000);
	assert(p.cantitate == 200);
	assert(strcmp(p.tip, "televizor") == 0);
	assert(strcmp(p.model, "v5000") == 0);
	assert(strcmp(p.producator, "tip1") == 0);

	addPr(l, p);
	assert(l->lg == 1);
	assert(l->produse[0].id == 1);
	assert(l->produse[0].pret == 1000);
	assert(l->produse[0].cantitate == 200);
	assert(strcmp(l->produse[0].tip, "televizor") == 0);
	assert(strcmp(l->produse[0].model, "v5000") == 0);
	assert(strcmp(l->produse[0].producator, "tip1") == 0);

	produs p2 = creeazaPr(2, "televizor", "p2", "v2", 100, 20);
	addPr(l, p2);
	assert(l->lg == 2);
	assert(l->produse[1].id == 2);
	assert(l->produse[1].pret == 100);
	assert(l->produse[1].cantitate == 20);
	assert(strcmp(l->produse[1].tip, "televizor") == 0);
	assert(strcmp(l->produse[1].model, "v2") == 0);
	assert(strcmp(l->produse[1].producator, "p2") == 0);
	

	assert(findPr(l, 1) == 0);
	assert(findPr(l, 3) == -1);

	delPr(l, 0);
	assert(l->lg == 1);

	destroy(l);
	
}