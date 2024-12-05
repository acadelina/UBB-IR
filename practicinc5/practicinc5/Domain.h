#pragma once
#include<iostream>
using namespace std;

class Tractor {
	int id;
	string denum;
	string tip;
	int nrRoti;
public:
	Tractor(int id, string denum, string tip, int nrRoti) :id{ id }, denum{ denum }, tip{ tip }, nrRoti{ nrRoti } {};
	int getid()
	{
		return this->id;
	}
	string getdenum()
	{
		return this->denum;
	}
	string gettip()
	{
		return tip;
	}
	int getRoti()
	{
		return nrRoti;
	}
	void setid(int n)
	{
		id = n;
	}
	void setdenum(string n)
	{
		denum = n;
	}
	void settip(string n)
	{
		tip = n;
	}
	void setRoti(int n)
	{
		nrRoti= n;
	}

};

void testDomain();