
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<stdio.h>
#include"prod.h"
#include"MyList.h"
#include"service.h"


void printAll(MyList* l)
{
	if (l->lg == 0)
		printf("Nu exista produse!\n");
	else
	{
		printf("Produse:\n");
		for (int i = 0; i < size(l); i++)
		{
			Produs p = get(l, i);
			printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", p.id, p.tip, p.producator, p.model, p.pret, p.cantitate);
		}
	}
}

void printmeniu()
{
	printf("1.Adauga produs \n2.Modifica pret/cantitate \n3.Sterge produs \n4.Afiseaza stoc ordonat \n5.Filtrare \n0.Iesire \n");
}

void uiAdd(MyList* manager)
{
	char tip[20], model[20] , prod[20] ;
	int id, pret, cant ;
	printf("Dati id: \n");
	scanf_s("%d", &id);
	printf("Dati tip: \n");
	scanf_s("%s", tip,20);
	printf("Dati producator: \n");
	scanf_s("%s", prod,20);
	printf("Dati model: \n");
	scanf_s("%s", model,20);
	printf("Dati pret: \n");
	scanf_s("%d", &pret);
	printf("Dati cantitate: \n");
	scanf_s("%d", &cant);

	int ok = adaugarePr(&manager, id, tip, prod, model, pret, cant);
	
	if (ok == 1)
		printf("Tipul dat este invalid.\n");
	else if (ok == 2)
		printf("Pretul dat este invalid.\n");
	else if (ok == 3)
		printf("Cantitatea data este invalida. \n");
	else if (ok == 4)
		printf("ID-ul dat este asociat deja unui alt produs. \n");
	else if (ok == 0)
		printf("Produs adaugat cu succes\n");
	else;
		//printf("%d", ok);

	printf("Avem %d produse \n", manager->lg);

	//printAll(manager);
}

void uiModif(MyList* m)
{
	printf("1.Modifica pret \n2.Modifica cantitate\n");
	int cmd;
	scanf("%d", &cmd);
	if (cmd == 1)
	{
		int pret, id;
		printf("Dati id: ");
		scanf("%d", &id);
		printf("Dati pret: ");
		scanf("%d", &pret);
		if (pret <= 0)
			printf("Pretul dat este invalid.\n");
		else
		{
			if (updatePret(m, id, pret) == 1)
			{
				printf("Pretul a fost modificat cu succes.\n");
				//printAll(&(m->listaPr));
			}
			else
				printf("ID-ul dat nu apartine unui produs.\n ");
		}
	}
	else if (cmd == 2)
	{
		int id, cant;
		printf("Dati id \n");
		scanf("%d", &id);
		printf("Dati cantitate \n");
		scanf("%d", &cant);
		if (cant <= 0)
			printf("Cantitatea data este invalida.\n");
		else
		{
			if (updateCant(m, id, cant))
			{
				printf("Cantitatea a fost modificata cu succes.\n");
				//printAll(&m->listaPr);
			}
			else
				printf("ID-ul dat nu apartine unui produs.\n ");
		}
	}
	else
		printf("Comanda invalida!\n");
}

void uiFiltr(MyList* m)
{
	int crit;
	printf("0.Producator\n1.Pret\n2.Cantitate");
	scanf("%d", &crit);
	MyList lf=creeazaVid();
	if (crit == 0)
	{
		char prod[50];
		printf("Dati producator: ");
		scanf("%s", prod);
		lf = filtrPr(m, &prod);
		printf("Produsele de la producatorul %s: \n", prod);
		printAll(&lf);
		distruge(&lf);
	}
	else if (crit == 1)
	{
		int pret;
		printf("Dati pretul: ");
		scanf("%d", &pret);
		lf = filtrPret(m, pret);
		printf("Produsele cu pretul %d: \n", pret);
		printAll(&lf);
		distruge(&lf);
	}
	else if (crit == 2)
	{
		int cant;
		printf("Dati cantitate: ");
		scanf("%d", &cant);
		lf = filtrCant(m, cant);
		printf("Produsele cu cantitatea %d: \n", cant);
		printAll(&lf);
		distruge(&lf);
	}
	else
	{
		printf("Comanda invalida!\n");
	}
}

void uiSterge(MyList* m)
{
	int id,ok;
	printf("Dati id-ul produsului: ");
	scanf("%d", &id);
	ok=sterge(m, id);
	if (ok)
		printf("Produsul a fost sters cu succes!\n");
	else
		printf("Nu exista produs cu id-ul dat!\n");
	//printAll(&m->listaPr);
}

void uiSort(MyList* m)
{
	int ord;
	printf("0.Crescator\n1.Descrescator\n");
	scanf("%d", &ord);
	sortare(m, ord);
	//printAll(&m->listaPr);
}

void run()
{
	int ok = 1;
	MyList manager = creeazaVid();
	Produs p = creeazaPr(1, "televizor", "m1", "p1", 100, 10);
	adaugarePr(&manager, 1, "televizor", "m1", "p1", 100, 10);
	
	printAll(&manager);

	//ManagerPr manager = createManager();
	while (ok)
	{
		printmeniu();
		printf("Dati comanda: ");
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 1)
		{
			uiAdd(&manager);
			printAll(&manager);
		}
		else if (cmd == 2)
		{
			uiModif(&manager);
			printAll(&manager);
		}
		else if (cmd == 3)
		{
			uiSterge(&manager);
			printAll(&manager);
		}
		else if (cmd == 4)
		{
			uiSort(&manager);
			printAll(&manager);
		}
		else if (cmd == 5)
		{
			uiFiltr(&manager);
		}
		else if (cmd == 0)
		{
			//distrugeMan(&manager);
			break;
		}
		else
			printf("Comanda invalida!\n");
	}
	distruge(&manager);

}

int main()
{
	//testIterateList();
	//testAdd();
	//testCreateDestroy();
	run();
}