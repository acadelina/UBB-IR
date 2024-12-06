#pragma once
#include"Domain.h"

class RepoExc {
	string msg;
public:
	RepoExc(string msg) :msg{ msg } {};
	//getter pentru mesajul exceptiei
	string getmsg()
	{
		return msg;
	}
};

class Repo {
	vector<Task> v;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	/*
	Functie care adauga un task la lista
	precond: task t
	*/
	void add(Task& t);
	/*
	Functie care valideaza un task
	precond task t
	*/
	void validare(Task& t);
	/*
	Functie care schimba starea unui task dupa id
	precond: id-int
			stare-string
	*/
	void schimbStare(int id, string stare);
	/*
	cauta un task dupa id
	precond id-int
	*/
	int cauta(int id);
	/*
	returneaza true daca taskul dat are programatorul dat
	precond : task t
			  p string
			 */
	bool searchP(Task t, string p);
	/*
	Returneaza lista de taskuri
	postcond: vector de taskuri
	*/
	vector<Task> getT();
};

void testRepo();