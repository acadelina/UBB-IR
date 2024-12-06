#pragma once
#include "disciplina.h"
#include "service.h"
#include"Myvector.h"

class DisConsole
{
private:
	DisServ& serv;
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
	void printAll(const Myvector<Disciplina>& Dlist);
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