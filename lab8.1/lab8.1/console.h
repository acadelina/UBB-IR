#pragma once
#include "disciplina.h"
#include "serviceDis.h"
#include <iostream>
#include "Export.h"

class DisConsole
{
private:
	DisServ& serv;
	void printRaport();
	/*
	Meniu adaugare
	*/
	void addDisUI();

	/*
	Meniu modificare
	*/
	void modifDisUI();

	/*
	Meniu stergere
	*/
	void removeDisUI();

	/*
	Mmeniu cautare
	*/
	void findDisUI();

	/*
	Afisare discipline
	*/
	void printAll(const vector<Disciplina>& Dlist);

	void printAllCont(const vector < Disciplina>& dList);
	void sortare();

	void filterDisUI();
	void printDis(Disciplina dis);
	/*
	Afisare meniu
	*/
	void printMeniu();
public:
	DisConsole(DisServ& dS) : serv{ dS } {};
	DisConsole(const DisConsole& dS) = delete;
	void start();

};