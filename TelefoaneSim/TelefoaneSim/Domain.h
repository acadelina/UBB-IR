#pragma once
#include<iostream>
using namespace std;

class Telefon {
	string tip;
	string model;
	string culoare;
	int an;
	int pret;
public:
	Telefon(string tip,string model,string culoare,int an,int pret):tip{tip},model{model},culoare{culoare},an{an},pret{pret}{}
	Telefon() = default;
	string gettip()
	{
		return this->tip;
	}
	string getmodel()
	{
		return this->model;
	}
	string getculoare()
	{
		return this->culoare;
	}
	int getan()
	{
		return this->an;
	}
	int getpret()
	{
		return this->pret;
	}

	void settip(string n)
	{
		this->tip = n;
	}

	void setmodel(string n)
	{
		this->model = n;
	}

	void setculoare(string n)
	{
		this->culoare = n;
	}

	void setan(int n)
	{
		this->an = n;
	}

	void setpret(int n)
	{
		this->pret = n;
	}
};

void testDomain();
