#pragma once
#include<iostream>
using namespace std;


class Joc {
	int id;
	int dim;
	string tabla;
	string jucator;
	string stare;
public:
	Joc(int id, int dim, string tabla, string jucator, string stare) :id{ id }, dim{ dim }, tabla{ tabla }, jucator{ jucator }, stare{ stare } {};
	int getid()
	{
		return this->id;
	}

	int getdim()
	{
		return this->dim;
	}

	string gettabla()
	{
		return this->tabla;
	}

	string getjuc()
	{
		return this->jucator;
	}

	string getstare()
	{
		return this->stare;
	}

	void setid(int n)
	{
		this->id = n;
	}

	void setdim(int n)
	{
		this->dim = n;
	}

	void settabla(string n)
	{
		this->tabla = n;
	}

	void setjuc(string n)
	{
		this->jucator = n;
	}

	void setstare(string n)
	{
		this->stare = n;
	}

};

void testDomain();