#include"repo.h"
#include"service.h"
#include"validator.h"
#include<stdlib.h>
#include<string.h>
#include<assert.h>

int adaugaPr(Prlist* l, int id, char tip[], char prod[], char model[], int pret, int cant)
{
	int val = validare( tip,  pret, cant);
	if (val == 0)
	{
		produs np = creeazaPr(id, tip, prod, model, pret, cant);
		int ex = findPr(l, id);
		if (ex != -1)
		{
			if ((strcmp(l->produse[ex].tip, tip) == 0 && strcmp(l->produse[ex].model, model) == 0 && strcmp(l->produse[ex].producator, prod) == 0 && l->produse[ex].pret == pret))
				l->produse->cantitate += cant;
			else
				return 4;
		}
			
		else {
			addPr(l, np);
			return 0;
		}
	}
	
	return val;
}

int updatePret(Prlist* l, int id, int pret)
{
	int ok = 0;
	for (int i = 0; i < l->lg; i++)
	{
		produs p = l->produse[i];
		if (p.id == id)
		{
			p.pret = pret;
			l->produse[i] = p;
			ok = 1;

		}

	}
	return ok;
}

int updateCant(Prlist* l, int id, int cant)
{
	int ok = 0;

	for (int i = 0; i < l->lg; i++)
	{
		produs p =l->produse[i];

		if (p.id == id)
		{

			p.cantitate = cant;
			l->produse[i] = p;
			ok = 1;

		}

	}
	return ok;

}

int sterge(Prlist* l, int id)
{
	int poz_del = findPr(l, id);
	if (poz_del != -1)
	{
		delPr(l, poz_del);
		
		return 0;
	}
	return 1;
}

Prlist filtrPr(Prlist* l, char* prod)
{
	Prlist nou = creeazaVid();
	for (int i = 0; i < l->lg; i++)
	{
		
		if (strcmp(l->produse[i].producator, prod) == 0)
		{
			nou.produse[nou.lg] = l->produse[i];
			nou.lg++;
			
		}
	}
	return nou;
}

Prlist filtrPret(Prlist* l, int pret)
{
	Prlist nou = creeazaVid();
	for (int i = 0; i < l->lg; i++)
	{
		produs p = l->produse[i];
		if (p.pret == pret)
		{
			nou.produse[nou.lg] = l->produse[i];
			nou.lg++;
			
		}
	}
	return nou;
}

Prlist filtrCant(Prlist* l, int cant)
{
	Prlist nou = creeazaVid();
	for (int i = 0; i <l->lg; i++)
	{
		produs p =l->produse[i];
		if (p.cantitate == cant)
		{
			nou.produse[nou.lg] = l->produse[i];
			nou.lg++;
			
		}
	}
	return nou;
}


int cmpModelAsc(const produs* p1, const produs* p2)
{
	if (p1->pret > p2->pret)
		return 1;
	else if (p1->pret == p2->pret && p1->cantitate > p2->cantitate)
		return 1;
	return -1;
}

int cmpModelDesc(const produs* p1, const produs* p2)
{
	if (p1->pret < p2->pret)
		return 1;
	else if (p1->pret == p2->pret && p1->cantitate < p2->cantitate)
		return 1;
	return -1;
}

void bsort(produs* p, int lg, int(* func)(produs* p1,produs* p2))
{
	int ok = 0;
	while (!ok)
	{
		ok = 1;
		for(int i=0;i<lg - 1;i++)
			if (func(&p[i], &p[i + 1]) > 0)
			{
				produs aux = p[i];
				p[i] = p[i + 1];
				p[i + 1] = aux;
				ok = 0;
			}
	}
}
Prlist* sortare(Prlist* l, int ord)
{
	if (ord == 0)
		bsort(l->produse, l->lg, cmpModelAsc);
	else if (ord == 1)
		bsort(l->produse, l->lg,  cmpModelDesc);
	return l;

}

void testServ()
{
	Prlist lt = creeazaVid(),*l=&lt;

	assert(adaugaPr(l, 1, "televizor", "p1", "m1", 130, 10) == 0);
	assert(adaugaPr(l, 2, "televizor", "p2", "m2", 200, 13) == 0);
	assert(adaugaPr(l, 3, "televizor", "p3", "m3", 500, 160) == 0);
	assert(adaugaPr(l, 4, "televizor", "p3", "m2", 500, 100) == 0);
	assert(adaugaPr(l, 5, "televizor", "p1", "m1", 100, 102) == 0);
	assert(adaugaPr(l, 1, "televizor", "p1", "m1", 130, 10) == 0);
	assert(l->produse[0].cantitate == 20);
	

	assert(adaugaPr(l, 1, "televizor", "p1", "m1", 100, 10) == 4);
	assert(adaugaPr(l, 6, "televizo", "p1", "m1", 100, 10) == 1);
	assert(adaugaPr(l, 6, "televizor", "p1", "m1", -100, 10) == 2);
	assert(adaugaPr(l, 6, "televizor", "p1", "m1", 100, -10) == 3);

	assert(updateCant(l, 1, 12) == 1);
	assert(updateCant(l, 6, 12) == 0);

	assert(updatePret(l, 1, 111) == 1);
	assert(updatePret(l, 6, 111) == 0);

	assert(sterge(l, 1) == 0);
	assert(sterge(l, 8) == 1);

	Prlist lf = filtrCant(l, 100);
	assert(lf.lg == 1);
	assert(lf.produse[0].id == 4);
	destroy(&lf);

	lf = filtrPr(l, "p3");
	assert(lf.lg == 2);
	assert(lf.produse[0].id == 3);
	assert(lf.produse[1].id == 4);
	destroy(&lf);

	lf = filtrPret(l, 500);
	assert(lf.lg == 2);
	assert(lf.produse[0].id == 3);
	assert(lf.produse[1].id == 4);
	destroy(&lf);

	sortare(l, 0);
	assert(l->produse[0].id == 5);
	assert(l->produse[1].id == 2);
	assert(l->produse[2].id == 4);
	assert(l->produse[3].id == 3);

	sortare(l, 1);
	assert(l->produse[0].id == 3);
	assert(l->produse[1].id == 4);
	assert(l->produse[2].id == 2);
	assert(l->produse[3].id == 5);

	destroy(l);
	
	//produs p = creeazaPr(1, "televizor", "tip1", "v5000", 1000, 200);
	//produs p2 = creeazaPr(2, "televizor", "p2", "v2", 100, 20);
	
}