#pragma once

//obiectul de tip produs
typedef struct {
	int id;
	char tip[50];
	char producator[50];
	char model[50];
	int pret;
	int cantitate;
}produs;

//lista care retine produsele
typedef struct
{
	//produse->vectorul de produse
	//lg-lungimea curenta
	//cap-capacitatea
	produs* produse;
	int lg;
	int cap;
}Prlist;
