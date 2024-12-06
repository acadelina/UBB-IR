#pragma once
using namespace std;
#include<iostream>

class Produs {
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, string nume, string tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {};
	//getter id
	int getid()
	{
		return id;
	}
	//getter nume
	string getnume()
	{
		return nume;
	}
	//getter tip
	string gettip()
	{
		return tip;
	}
	//getter pret
	double getpret()
	{
		return pret;
	}
	//setter id
	//prec:n-int
	void setid(int n)
	{
		this->id = n;
	}
	//setter nume
	//prec:n-string
	void setnume(string n)
	{
		this->nume = n;
	}
	//setter tip
	//prec:n-string
	void settip(string n)
	{
		this->tip = n;
	}
	//setter pret
	//prec:n-double
	void setpret(double n)
	{
		this->pret = n;
	}
};