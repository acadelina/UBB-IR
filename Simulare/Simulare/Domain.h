#pragma once
#include<iostream>
using namespace std;
class Rochie {
	int cod;
	string denum;
	string marime;
	int pret;
	bool disp;

public:
	Rochie(int cod,string denum,string marime,int pret,bool disp):cod{cod},denum{denum},marime{marime},pret{pret},disp{disp}{}
	//getere
	int getcod()
	{
		return this->cod;
	}

	int getpret()
	{
		return this->pret;
	}

	string getdenum()
	{
		return this->denum;
	}

	string getmarime()
	{
		return this->marime;
	}

	bool getdisp()
	{
		return this->disp;
	}

	//setere
	void setcod(int n)
	{
		this->cod = n;
	}

	void setpret(int n)
	{
		this->pret= n;
	}
	
	void setdenum(string n)
	{
		this->denum= n;
	}

	void setmarime(string n)
	{
		this->marime = n;
	}

	void setdisp(bool n)
	{
		this->disp= n;
	}
};

void testDomain();