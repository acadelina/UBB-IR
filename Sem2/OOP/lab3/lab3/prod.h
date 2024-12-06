#pragma once

typedef struct {
	int id;
	char* tip;
	char* producator;
	char* model;
	int pret;
	int cantitate;
}Produs;

/*
Creeaza produs nou
*/
Produs creeazaPr(int id, char* tip, char* prod, char* model, int pret, int cant);

/*
Dealocare memorie
*/
void distrugePr(Produs* p);

//void testCreeazaDistruge();
Produs CopyPr(Produs* p);

int getPret(Produs*);

int getCant(Produs*);

char* getTip(Produs*);

char* getProd(Produs*);

char* getModel(Produs*);

int getId(Produs*);

int valideaza(Produs p);

void testCreateDestroy();
