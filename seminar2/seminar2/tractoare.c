#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

typedef struct {
	char nume[20];
	int anFabr;
}Tractor;

typedef struct {
	Tractor trs[100];
	int lg;
}ListaMea;

void f()
{
	int* p = malloc(sizeof(int));
	*p = 42;
	free(p);

}

Tractor creeazaTr(char* nume, int anFabr)
{
	Tractor rez;
	strcpy(rez.nume, nume);
	rez.anFabr = anFabr;
	return rez;
}
/*
 Tractor creeazaTr(char* nume, int anFabr)
{
	Tractor rez;
	int lg=strlen(nume)+1;
	rez.nume=malloc(lg);
	strcpy(rez.nume, nume);
	rez.anFabr = anFabr;
	return rez;
}
*/
ListaMea creeazaVid()
{
	ListaMea rez;
	rez.lg = 0;
	return rez;
}
void adauga(ListaMea *l, Tractor t)
{

	l->trs[l->lg] = t;
	l->lg++;

}
int lungime(ListaMea *l)
{
	return l->lg;
}

void testAdauga()
{
	ListaMea l = creeazaVid();
	assert(lungime(&l) == 0);
	adauga(&l, creeazaTr("Vasi", 2010));
	assert(lungime(&l) == 1);
	adauga(&l, creeazaTr("Ana", 2011));
	assert(lungime(&l) == 2);


}
void adaugaTractor(ListaMea* l, char* nume, int anFabr)
{
	Tractor tr = creeazaTr(nume, anFabr);
	//validare
	adauga(l, tr);
}
void afis(ListaMea* l)
{
	for (int i = 0; i < lungime(l); i++)
	{
		Tractor tr = l->trs[i];
		printf("%d, %s \n", tr.anFabr, tr.nume);
	}
}
void startApp()
{
	ListaMea trs = creeazaVid();
	while (1)
	{
		printf("1.Adauga tractor \n Iesire \n");
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 0)
			break;
		else if (cmd == 1)
		{
			char nume[20];
			printf("Dati nume: \n");
			scanf("%s", nume);
			int an;
			printf("Dati an: \n");
			scanf("%d", &an);
			adaugaTractor(&trs, nume, an);
			printf("Avem %d tractoare", lungime(&trs));
			afis(&trs);

		}
	}
}
void runAllTest()
{
	testAdauga();
}
int main()
{
	runAllTest();
	ListaMea tractoare;
	startApp();
	return 0;
}