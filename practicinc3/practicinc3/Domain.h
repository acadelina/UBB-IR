#pragma once
#include<iostream>
using namespace std;

class Produs {
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, string nume, string tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {};
	int getid()
	{
		return this->id;
	}
	string getnume()
	{
		return this->nume;
	}
	string gettip()
	{
		return this->tip;
	}
	double getpret()
	{
		return this->pret;
	}
	void setid(int n)
	{
		this->id = n;
	}
	void setnume(string n)
	{
		this->nume = n;
	}
	void settip(string n)
	{
		this->tip = n;
	}
	void setpret(double n)
	{
		this->pret = n;
	}
	int getvocale()
	{
		int nr = 0;
		for (auto i : nume)
			if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
				nr++;
		return nr;
	}

};
void testDomain();