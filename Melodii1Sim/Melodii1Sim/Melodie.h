#pragma once
#include<iostream>
#include<string>
using namespace std;

class Produs {
private:
	int id;
	string nume;
	string tip;
	int pret;
	string producator;
public:
	Produs(int id, const string nume, const string tip, int pret, const string producator) :id{ id },nume { nume }, tip{ tip }, pret{ pret }, producator{ producator } {}
	Produs() :id{ 0 }, nume { "" }, tip{ "" }, pret{ 0 }, producator{ "" } {};
	int getId()const {
		return this->id;
	}
	void setId(int n) {
		this->id = n;
	}
	string getNume()const {
		return this->nume;
	}

	string getTip()const {
		return this->tip;
	}

	string getProd()const {
		return this->producator;
	}

	int getPret()const {
		return this->pret;
	}

	void setNume(string n)
	{
		this->nume = n;
	}

	void setTip(string n)
	{
		this->tip = n;
	}

	void setProd(string n)
	{
		this->producator = n;
	}

	void setPret(int n)
	{
		this->pret = n;
	}

	
};

void testDomain();

