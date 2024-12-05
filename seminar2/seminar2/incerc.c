#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<string.h>

typedef struct {
	int id;
	char tip[25];
	char producator[50];
	char model[50];
	int pret;
	int cantitate;
}Produs;

typedef struct {
	Produs prod[100];
	int lg;
}Lista;

Lista creeazaVid()
{
	Lista rez;
	rez.lg = 0;
	return rez;
}
Produs creeazaPr(int id, char* tip, char* prod, char* model, int pret, int cant)
{
	Produs rez;
	rez.id = id;
	strcpy(rez.tip, tip);
	strcpy(rez.model, model);
	strcpy(rez.producator, prod);
	rez.cantitate = cant;
	rez.pret = pret;
	return rez;
}
void adauga(Lista* l, Produs p)
{
	printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", p.id, p.tip, p.producator, p.model, p.pret, p.cantitate);
	l->prod[l->lg] = p;
	l->lg++;
}
int lungime(Lista* l)
{
	return l->lg;
}
void afisareProd(Lista* l)
{
	Produs p;
	for (int i = 0; i < lungime(l); i++)
	{
		p = *l[i].prod;
		int a = l[i].prod->id;
		printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", a, p.tip, p.producator, p.model, p.pret, p.cantitate);
	}
}
void testAdauga()
{
	Lista l = creeazaVid();
	assert(lungime(&l) == 0);
	adauga(&l, creeazaPr(1,"televizor","tip1","v5000",1000,200));
	assert(lungime(&l) == 1);
	adauga(&l, creeazaPr(1, "televizor", "tip2", "v7000", 1500, 20));
	assert(lungime(&l) == 2);


}

void adaugaPr(Lista* l, int id, char* tip, char* prod, char* model, int pret, int cant)
{
	char *tipuri[4] = { "laptop", "frigider", "televizor", "altceva" };
	int ok = 0;
	for (int i = 0; i < 4; i++)
	{

		if (strcmp(tipuri[i], tip) == 0)
			ok = 1;
	}
	if (!ok)
		printf( "Tipul dat este invalid.\n");
	if (pret <= 0)
	{
		printf("Pretul dat este invalid.\n");
		ok = 0;
	}
	if (cant <= 0)
	{
		printf("Cantitatea data este invalida. \n");
		ok = 0;

	}
	if (ok!=0)
	{
		ok = 1;
		
		Produs pr = creeazaPr(id, tip, prod, model, pret, cant);
		printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", pr.id, pr.tip, pr.producator, pr.model, pr.pret, pr.cantitate);
		for (int i = 0; i < lungime(l); i++)
		{
			Produs p = *l[i].prod;
			
			if (p.id == id)
			{
				ok = 0;
				if (strcmp(p.tip, tip) == 0 && strcmp(p.model, model)==0 && strcmp(p.producator, prod)==0 && p.pret == pret)
				{
					p.cantitate = p.cantitate + cant;
					*l[i].prod = p;
				}
				else
					printf("ID-ul dat este asociat deja unui alt produs. \n");
			}
		}
		if (ok == 1)
		{
			printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", pr.id, pr.tip, pr.producator, pr.model, pr.pret, pr.cantitate);
			adauga(l, pr);
		}
		
	}


		
}
int updatePret(Lista* l, int id, int pret)
{
	int ok = 0;
	for (int i = 0; i < lungime(l);i++)
	{
		Produs p = *l[i].prod;
		if (p.id == id)
		{
			p.pret = pret;
			*l[i].prod = p;
			ok = 1;
			
		}

	}
	if (ok == 0)
		return 0;
	else
		return 1;

}
void test_update()
{
	Lista l = creeazaVid();

	assert(lungime(&l) == 0);
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	assert(lungime(&l) == 1);
	assert(updateCant(&l, 1, 20)==1);
	assert(updateCant(&l, 2, 20) == 0);
	assert(updatePret(&l, 1, 100) == 1);
	assert(updateCant(&l, 5, 100) == 0);
	

}
int updateCant(Lista* l, int id, int cant)
{
	int ok = 0;
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = *l[i].prod;
		if (p.id == id)
		{
			p.cantitate = cant;
			*l[i].prod = p;
			ok = 1;
			
		}

	}
	if (ok == 0)
		return 0;
	else
		return 1;

}
void modifPret(Lista* l, int id, int pret)
{
	if (pret <= 0)
		printf("Pretul dat este invalid.\n");
	else
	{
		if (updatePret(&l, id, pret))
		{
			printf("Pretul a fost modificat cu succes.\n");
			afisareProd(&l);
		}
		else
			printf("ID-ul dat nu apartine unui produs.\n ");
	}
}
void modifCant(Lista* l, int id, int cant)
{
	if (cant <= 0)
		printf("Cantitatea data este invalida.\n");
	else
	{
		if (updateCant(&l, id, cant))
		{
			printf("Cantitatea a fost modificata cu succes.\n");
			afisareProd(&l);
		}
		else
			printf("ID-ul dat nu apartine unui produs.\n ");
	}
}
void testAdaugaPr()
{
	Lista l = creeazaVid();
	assert(lungime(&l) == 0);
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 2, "televizor", "tip2", "v5000", -1000, 200);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 20);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 2, "televizor", "tip7", "v1000", 1000, 20);
	assert(lungime(&l) == 2);
	//adaugaPr(&l, 2, "televizor", "tip7", "v1000", 1000, 39);
	//assert(lungime(&l) == 2);

}
int sterge(Lista* l, int id)
{
	int ind, ok = 0;
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = *l[i].prod;
		if (p.id == id)
		{
			ok = 1;
			ind = i;
		}
	}
	if (ok == 0)
		return 0;
	for (int i = ind; i < lungime(l) - 1; i++)
	{
		*l[i].prod = *l[i + 1].prod;

	}
	l->lg--;
	return 1;

}
void testSterge()
{
	Lista l = creeazaVid();
	assert(lungime(&l) == 0);
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 2, "televizor", "tip2", "v3000", 2000, 200);
	assert(lungime(&l) == 2);
	sterge(&l, 1);
	assert(lungime(&l) == 1);
	assert(sterge(&l, 3)==0);
	assert(lungime(&l) == 1);

}
void stergeProd(Lista* l, int id)
{
	if (sterge(&l, id))
	{
		printf("Stergere efectuata cu succes \n");
		afisareProd(&l);
	}
	else
		printf("PID-ul dat nu apartine unui produs \n");
}

void startApp()
{
	Lista prs = creeazaVid();
	while (1)
	{
		printf("1.Adauga produs \n2.Modifica pret/cantitate \n3.Sterge produs \n0.Iesire \n");
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 0)
			break;
		else if (cmd == 1)
		{
			char tip[20]="", model[20]="", prod[20]="";
			int id=0, pret=0, cant=0;
			printf("Dati id: \n");
			scanf("%d", &id);
			printf("Dati tip: \n");
			scanf("%s", tip);
			printf("Dati producator: \n");
			scanf("%s", prod);
			printf("Dati model: \n");
			scanf("%s", model);
			printf("Dati pret: \n");
			scanf("%d", &pret);
			printf("Dati cantitate: \n");
			scanf("%d", &cant);
			adaugaPr(&prs, id, tip, prod, model, pret, cant);
			printf("Avem %d produse \n", lungime(&prs));
			afisareProd(&prs);
		}
		else if (cmd == 2)
		{
			int c,pret,cant,id;
			printf("1.Modifica pret \n2.Modifica cantitate\n");
			scanf("%d", &c);
			if (c == 1)
			{
				printf("Dati id \n");
				scanf("%d", &id);
				printf("Dati pret \n");
				scanf("%d", &pret);
				modifPret(&prs, id, pret);
			}
			else if (c == 2)
			{
				printf("Dati id \n");
				scanf("%d", &id);
				printf("Dati cantitate \n");
				scanf("%d", &cant);
				modifCant(&prs, id, cant);
			}
			else
				printf("Comanda invalida!\n");

		}
		else if (cmd == 3)
		{
			int id;
			printf("Dati id-ul produsului cautat: ");
			scanf("%d", &id);
			stergeProd(&prs, id);
		}
	}
}
void runAllTest()
{
	testAdauga();
	testAdaugaPr();
	test_update();
	testSterge();
}
int main()
{
	runAllTest();
	Lista produse;
	startApp();
	return 0;
}
