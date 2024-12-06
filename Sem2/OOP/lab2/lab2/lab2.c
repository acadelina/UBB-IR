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
	/*
	Functie care creeaza o structura lista vida
	preconditii:
	postcondiii: rez->Lista
	*/
	Lista rez;
	rez.lg = 0;
	return rez;
}
Produs creeazaPr(int id, char* tip, char* prod, char* model, int pret, int cant)
{
	/*
	Functie care creeaza un produs
	precond:id->int
			tip->char
			prod->char
			model->char
			pret->int
			cant->int
	postcond:rez->Produs
	*/
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
	/*
	Functie cara adauga un produs in lista
	precond:l->Lista
			p->Produs
	postcond:
	*/
	l->prod[l->lg] = p;
	l->lg++;
}
int lungime(Lista* l)
{
	/*
	Functie care returneza lungimea listei date
	precond: l->Lista
	postcond: l->lg:int
	*/
	return l->lg;
}
void afisareProd(Lista* l)
{
	/*
	Functie care afuseaza produsele dintr-o lista data
	precond: l->Lista
	postcond:
	*/
	Produs p;
	for (int i = 0; i < lungime(l); i++)
	{
		p = l->prod[i];
		int a = l[i].prod->id;
		printf("Id: %d, tip:%s, producator:%s, model:%s, pret:%d, cantitate:%d \n", p.id, p.tip, p.producator, p.model, p.pret, p.cantitate);
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

int adaugaPr(Lista* l, int id, char* tip, char* prod, char* model, int pret, int cant)
{
	/*
	Functie care adauga un produs sau creste stocul daca acesta exista deja
	precond:l->Lista
			id->int
			tip->char
			prod->char
			model->char
			pret->int
			cant->int
	postcond:
	*/
	char *tipuri[4] = { "laptop", "frigider", "televizor", "altceva" };
	
	int ok = 0;
	for (int i = 0; i < 4; i++)
	{

		if (strcmp(tipuri[i], tip) == 0)
			ok = 1;
	}
	if (!ok)
		return 1;
		//strcat(erori, "Tipul dat este invalid.\n");
		//printf( "Tipul dat este invalid.\n");
	if (pret <= 0)
	{
		return 2;
		//strcat(erori, "Pretul dat este invalid.\n");
		//printf("Pretul dat este invalid.\n");
		
	}
	if (cant <= 0)
	{
		return 3;
		//strcat(erori, "Cantitatea data este invalida. \n");
		//printf("Cantitatea data este invalida. \n");
		

	}
	if (ok!=0)
	{
		ok = 1;
		
		Produs pr = creeazaPr(id, tip, prod, model, pret, cant);
		
		for (int i = 0; i < lungime(l); i++)
		{
			Produs p = (l->prod)[i];
			
			if (p.id == id)
			{
				ok = 0;
				if (strcmp(p.tip, tip) == 0 && strcmp(p.model, model) == 0 && strcmp(p.producator, prod) == 0 && p.pret == pret)
				{
					p.cantitate = p.cantitate + cant;
					*l[i].prod = p;
				}
				else
					return 4;
					//strcat(erori, "ID-ul dat este asociat deja unui alt produs. \n");
					//printf("ID-ul dat este asociat deja unui alt produs. \n");
			}
		}
		if (ok == 1)

			adauga(l, pr);
			
		return 0;
		
	}


		
}
int updatePret(Lista* l, int id, int pret)
{
	/*
	Functie care schimba pretul unui produs
	precond: l->Lista
			 id->int
			 pret->int
	postcond:1/0 daca produsul exista sau nu
	*/
	int ok = 0;
	for (int i = 0; i < lungime(l);i++)
	{
		Produs p = l->prod[i];
		if (p.id == id)
		{
			p.pret = pret;
			l->prod[i] = p;
			ok = 1;
			
		}

	}
	if (ok == 0)
		return 0;
	else
		return 1;

}

int updateCant(Lista* l, int id, int cant)
{
	/*
	Functie care schimba cantitatea unui produs
	precond: l->Lista
			 id->int
			 cant->int
	postcond:1/0 daca produsul exista sau nu
	*/
	int ok = 0;
	
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = l->prod[i];
		
		if (p.id == id)
		{
			
			p.cantitate = cant;
			l->prod[i]= p;
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
	assert(updateCant(&l, 1, 20) == 1);
	assert(updateCant(&l, 2, 20) == 0);
	assert(updatePret(&l, 1, 100) == 1);
	assert(updatePret(&l, 2, 20) == 0);
	assert(updateCant(&l, 5, 100) == 0);


}
void modifPret(Lista* l, int id, int pret)
{
	/*
	Functie meniu pentru modificare pret
	preconditii:l->Lista
				id->int
				pret->int
	postcond:
	*/
	if (pret <= 0)
		printf("Pretul dat este invalid.\n");
	else
	{
		if (updatePret(l, id, pret)==1)
		{
			printf("Pretul a fost modificat cu succes.\n");
			afisareProd(l);
		}
		else
			printf("ID-ul dat nu apartine unui produs.\n ");
	}
}
void modifCant(Lista* l, int id, int cant)
{
	/*
	Functie meniu pentru modificare cantitate
	preconditii:l->Lista
				id->int
				pret->int
	postcond:
	*/
	if (cant <= 0)
		printf("Cantitatea data este invalida.\n");
	else
	{
		if (updateCant(l, id, cant))
		{
			printf("Cantitatea a fost modificata cu succes.\n");
			afisareProd(l);
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
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 20);
	assert(lungime(&l) == 1);
	adaugaPr(&l, 2, "televizor", "tip7", "v1000", 1000, 20);
	assert(lungime(&l) == 2);
	int e= adaugaPr(&l, 2, "tele", "tip7", "v1000", 1000, 20);
	assert(e == 1);
	e = adaugaPr(&l, 2, "televizor", "tip7", "v1000", -1000, 20);
	assert(e == 2);
	e = adaugaPr(&l, 2, "televizor", "tip7", "v1000", 1000, -20);
	assert(e == 3);
	e = adaugaPr(&l, 2, "televizor", "tip6", "v1000", 1000, 20);
	assert(e == 4);

}
int sterge(Lista* l, int id)
{
	/*
	Functie care sterge un produs dupa id
	precond:l->Lista
			id->int
	postcond:1/0 daca produsul exista sau nu
	*/
	int ind, ok = 0;
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = l->prod[i];
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
		l->prod[i] = l->prod[i + 1];

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
	/*
	Functie de meniu pentru stergere
	precond:l->Lista
			id->int
	postcond:
	*/
	if (sterge(l, id))
	{
		printf("Stergere efectuata cu succes \n");
		afisareProd(l);
	}
	else
		printf("PID-ul dat nu apartine unui produs \n");
}

void swap(Produs* a, Produs* b)
{
	/*
	Functie de interschimbare a doua produse
	precond: a,b->Produs
	postcond:
	*/
	Produs aux = *a;
	*a = *b;
	*b = aux;

}
void testSwap()
{
	Produs a, b;
	a = creeazaPr(1, "televizor", "p1", "m1", 100, 10);
	b= creeazaPr(2, "televizor", "p2", "m2", 200, 90);
	swap(&a, &b);
	assert(a.id == 2);
	assert(b.id == 1);
	assert(a.pret == 200);
	assert(b.pret == 100);
	

}
void sortare(Lista* l, int ord)
{
	/*
	Functie de sortare
	prcond:l->Lista
		   ord->int
	postcond:
	*/
	int i, j, ok;
	if (ord == 0)
	{
		for (i = 0; i < lungime(l); i++)
		{
			ok = 0;
			for (j = 0; j < lungime(l) - 1; j++)
			{
				if (((l->prod[j]).pret > (l->prod[j + 1]).pret) || ((l->prod[j]).pret == (l->prod[j + 1]).pret && (l->prod[j]).cantitate > (l->prod[j + 1]).cantitate))
				{
					swap(&(l->prod[j]), &(l->prod[j + 1]));
					ok = 1;
				}
			}
			if (ok == 0)
				break;
		}
	}
	else
	{
		for (i = 0; i < lungime(l); i++)
		{
			ok = 0;
			for (j = 0; j < lungime(l) - 1; j++)
			{
				if (((l->prod[j]).pret < (l->prod[j + 1]).pret) || ((l->prod[j]).pret == (l->prod[j + 1]).pret && (l->prod[j]).cantitate < (l->prod[j + 1]).cantitate))
				{
					swap(&(l->prod[j]), &(l->prod[j + 1]));
					ok = 1;
				}
			}
			if (ok == 0)
				break;
		}
	}
	
}
void testSortare()
{
	Lista l = creeazaVid();
	
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	adaugaPr(&l, 3, "televizor", "tip3", "v1000", 1000, 100);
	adaugaPr(&l, 2, "televizor", "tip2", "v3000", 2000, 200);
	sortare(&l, 0);
	assert((l.prod[0]).id == 3);
	assert((l.prod[1]).id == 1);
	assert((l.prod[2]).id == 2);
	sortare(&l, 1);
	assert((l.prod[0]).id == 2);
	assert((l.prod[1]).id == 1);
	assert((l.prod[2]).id == 3);

}
Lista filtrProd(Lista* l, char* prod)
{
	/*
	Functie care creeaza o lista cu produsele ce au producatorul dat
	precond: l->Lista
			 prod->char
	postcond: nou->Lista
	*/
	Lista nou = creeazaVid();
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = l->prod[i];
		if (strcmp(p.producator, prod) == 0)
		{
			adauga(&nou, p);
		}
	}
	return nou;
}
void testFiltrProd()
{
	Lista l = creeazaVid();
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	adaugaPr(&l, 3, "televizor", "tip1", "v1000", 1000, 100);
	adaugaPr(&l, 2, "televizor", "tip2", "v3000", 2000, 200);
	Lista lf;
	lf = filtrProd(&l, "tip2");
	assert(lungime(&lf) == 1);
	lf = filtrProd(&l, "tip1");
	assert(lungime(&lf) == 2);
	lf = filtrProd(&l, "tip3");
	assert(lungime(&lf) == 0);

}
Lista filtrPret(Lista* l, int pret)
{
	/*
	Functie care creeaza o lista cu produsele ce au pretul dat
	precond: l->Lista
			 pret->int
	postcond: nou->Lista
	*/
	Lista nou = creeazaVid();
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = l->prod[i];
		if (p.pret==pret)
		{
			adauga(&nou, p);
		}
	}
	return nou;
}
void testFiltrPret()
{
	Lista l = creeazaVid();
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	adaugaPr(&l, 3, "televizor", "tip3", "v1000", 1000, 100);
	adaugaPr(&l, 2, "televizor", "tip2", "v3000", 2000, 200);
	Lista lf;
	lf = filtrPret(&l, 2000);
	assert(lungime(&lf) == 1);
	lf = filtrPret(&l, 1000);
	assert(lungime(&lf) == 2);
	lf = filtrPret(&l, 50);
	assert(lungime(&lf) == 0);

}
Lista filtrCant(Lista* l, int cant)
{
	/*
	Functie care creeaza o lista cu produsele ce au cantitatea data
	precond: l->Lista
			 cant->int
	postcond: nou->Lista
	*/
	Lista nou = creeazaVid();
	for (int i = 0; i < lungime(l); i++)
	{
		Produs p = l->prod[i];
		if (p.cantitate==cant)
		{
			adauga(&nou, p);
		}
	}
	return nou;
}
void testFiltrCant()
{
	Lista l = creeazaVid();
	adaugaPr(&l, 1, "televizor", "tip1", "v5000", 1000, 200);
	adaugaPr(&l, 3, "televizor", "tip3", "v1000", 1000, 100);
	adaugaPr(&l, 2, "televizor", "tip2", "v3000", 2000, 200);
	Lista lf;
	lf = filtrCant(&l, 100);
	assert(lungime(&lf) == 1);
	lf = filtrCant(&l, 200);
	assert(lungime(&lf) == 2);
	lf = filtrCant(&l, 50);
	assert(lungime(&lf) == 0);

}
void filtrare(Lista* l, int crit)
{
	/*
	Functie de meniu pt filtrare
	precond: l->Lista
			 crit->int
	postcond:
	*/
	Lista lf;
	if (crit == 0)
	{
		char prod[50];
		printf("Dati producator: ");
		scanf("%s", prod);
		lf = filtrProd(l, &prod);
		printf("Produsele de la producatorul %s: \n", prod);
		afisareProd(&lf);
	}
	else if (crit == 1)
	{
		int pret;
		printf("Dati pretul: ");
		scanf("%d", &pret);
		lf = filtrPret(l, pret);
		printf("Produsele cu pretul %d: \n", pret);
		afisareProd(&lf);
	}
	else if (crit == 2)
	{
		int cant;
		printf("Dati cantitate: ");
		scanf("%d", &cant);
		lf = filtrCant(l, cant);
		printf("Produsele cu cantitatea %d: \n", cant);
		afisareProd(&lf);
	}
	else
	{
		printf("Comanda invalida!\n");
	}
}
void startApp()
{
	Lista prs = creeazaVid();
	while (1)
	{
		printf("1.Adauga produs \n2.Modifica pret/cantitate \n3.Sterge produs \n4.Afiseaza stoc ordonat \n5.Filtrare \n0.Iesire \n");
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
			int e=adaugaPr(&prs, id, tip, prod, model, pret, cant);
			if (e==1)
				printf("Tipul dat este invalid.\n");
			else if(e==2)
				printf("Pretul dat este invalid.\n");
			else if(e==3)
				printf("Cantitatea data este invalida. \n");
			else if(e==4)
				printf("ID-ul dat este asociat deja unui alt produs. \n");
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
		else if (cmd == 4)
		{
			int ord;
			printf("0.Crescator\n1.Descrescator\n");
			scanf("%d", &ord);
			sortare(&prs, ord);
			afisareProd(&prs);
		}
		else if (cmd == 5)
		{
			int crit;
			printf("0.Producator\n1.Pret\n2.Cantitate");
			scanf("%d", &crit);
			filtrare(&prs, crit);
		}
	}
}
void runAllTest()
{
	testAdauga();
	testAdaugaPr();
	test_update();
	testSterge();
	testSwap();
	testSortare();
	testFiltrCant();
	testFiltrPret();
	testFiltrProd();
}
int main()
{
	runAllTest();
	Lista produse;
	startApp();
	return 0;
}
