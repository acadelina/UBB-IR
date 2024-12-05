#pragma once
#include"melodie.h"
#include"Repo.h"
#include<map>

class Serv {
	Repo& repo;
public:
	Serv(Repo& repo) :repo{ repo } {};
	vector<Melodie> getAll();
	map<int,int> sameR();
	void modificR(int r, int id);
	void modificT(int id, string titlu);
	void sterge(int id);
};

void testServ();