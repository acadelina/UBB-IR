
#include"service.h"
#include"validator.h"
#include<stdio.h>

void printMeniu()
{
	printf("1.Adauga produs \n2.Modifica pret/cantitate \n3.Sterge produs \n4.Afiseaza stoc ordonat \n5.Filtrare \n0.Iesire \n");
}

void printList(Prlist* l)
{
	for (int i = 0; i < l->lg; i++)
	{
		printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", l->produse[i].id, l->produse[i].tip, l->produse[i].producator, l->produse[i].model, l->produse[i].pret, l->produse[i].cantitate);
	}
}

void addPrUi(Prlist* l)
{
	char tip[20], model[20], prod[20];
	int id, pret, cant,x;
	printf("Dati id: \n");
	x=scanf("%d", &id);
	printf("Dati tip: \n");
	x=scanf("%s", tip);
	printf("Dati producator: \n");
	x=scanf("%s", prod);
	printf("Dati model: \n");
	x=scanf("%s", model);
	printf("Dati pret: \n");
	x=scanf("%d", &pret);
	printf("Dati cantitate: \n");
	x=scanf("%d", &cant);

	int ok = adaugaPr(l, id, tip, prod, model, pret, cant);

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

	printf("Avem %d produse \n", l->lg);

	//printAll(manager);
}
void uiModif(Prlist* m)
{
	printf("1.Modifica pret \n2.Modifica cantitate\n");
	int cmd,x;
	x=scanf("%d", &cmd);
	if (cmd == 1)
	{
		int pret, id;
		printf("Dati id: ");
		x=scanf("%d", &id);
		printf("Dati pret: ");
		x=scanf("%d", &pret);
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
		x=scanf("%d", &id);
		printf("Dati cantitate \n");
		x=scanf("%d", &cant);
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

void uiFiltr(Prlist* m)
{
	int crit,x;
	printf("0.Producator\n1.Pret\n2.Cantitate");
	x=scanf("%d", &crit);
	Prlist lf;
	if (crit == 0)
	{
		
		char prod[50];
		printf("Dati producator: ");
		x=scanf("%s", prod);
		lf = filtrPr(m, prod);
		printf("Produsele de la producatorul %s: \n", prod);
		printList(&lf);
		destroy(&lf);
		//destroy(lf);
		printf("\n");
		
	}
	else if (crit == 1)
	{
		//Prlist 
		
		int pret;
		printf("Dati pretul: ");
		x=scanf("%d", &pret);
		lf = filtrPret(m, pret);
		printf("Produsele cu pretul %d: \n", pret);
		printList(&lf);
		//destroy(lf);
		printf("\n");
		destroy(&lf);
	}
	else if (crit == 2)
	{
		//Prlist
		
		int cant;
		printf("Dati cantitate: ");
		x=scanf("%d", &cant);
		lf = filtrCant(m, cant);
		printf("Produsele cu cantitatea %d: \n", cant);
		printList(&lf);
		//destroy(lf);
		printf("\n");
		destroy(&lf);
	}
	else
	{
		printf("Comanda invalida!\n");
	}
	
}

void uiSterge(Prlist* m)
{
	int id, ok,x;
	printf("Dati id-ul produsului: ");
	x=scanf("%d", &id);
	ok = sterge(m, id);
	if (ok==0)
		printf("Produsul a fost sters cu succes!\n");
	else
		printf("Nu exista produs cu id-ul dat!\n");
	//printAll(&m->listaPr);
}

void uiSort(Prlist* m)
{
	int ord,x;
	printf("0.Crescator\n1.Descrescator\n");
	x=scanf("%d", &ord);
	sortare(m, ord);
	//printAll(&m->listaPr);
}

void teste()
{
	testRepo();
	testServ();
	testVal();
}
void run()
{
	Prlist lt = creeazaVid(),* l=&lt;
	int cmd,x;
	while (1)
	{
		printf("Lista curenta:\n");
		printList(l);
		printMeniu();
		x=scanf("%d", &cmd);
		if (cmd == 1)
			addPrUi(l);
		else if (cmd == 2)
		{
			uiModif(l);
			
		}
		else if (cmd == 3)
		{
			uiSterge(l);
			
		}
		else if (cmd == 4)
		{
			uiSort(l);
			
		}
		else if (cmd == 5)
		{
			uiFiltr(l);
		}
		else if (cmd == 0)
		{
			destroy(l);
			
			break;
		}
		else
			printf("Comanda invalida!\n");
	}
}