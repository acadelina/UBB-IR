#pragma once
#include"Repo.h"
#include"Validator.h"

class Serv {
private:
	FileRepo& repo;
	Validator& val;
public:
	Serv(FileRepo& repo,Validator& val):repo{repo},val{val}{}
	void adaugare(int id, string nume, string tip, int pret, string producator);
	void stergere(int id, string nume, string tip, int pret, string producator);
	void modificare(int id, string nume, string tip, int pret, string producator);
	vector<Produs> filtrarePret(int pret);
	vector<Produs> filtrareNume(string nume);
	vector<Produs> sortareNume(int o);
	vector<Produs> sortarePret(int o);
	
	vector<Produs> getList();
};
//bool cmpNume(const Produs& p1,const Produs& p2);
	//bool cmpPret(Produs& p1, Produs& p2);