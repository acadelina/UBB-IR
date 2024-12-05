#pragma once
#include<iostream>
using namespace std;

class Melodie {
	int id;
	string titlu;
	string artist;
	string gen;
public:
	Melodie(int id, string t, string a, string g) :id{ id }, titlu{ t }, artist{ a }, gen{ g } {};
	int getid()
	{
		return this->id;
	}
	string gettitlul()
	{
		return this->titlu;
	}
	string getartist()
	{
		return this->artist;
	}
	string getgen()
	{
		return this->gen;
	}

	void setid(int n)
	{
		this->id = n;
	}
	void settitlu(string n)
	{
		this->titlu = n;
	}
	void setartist(string n)
	{
		this->artist = n;
	}
	void setgen(string n)
	{
		this->gen = n;
	}

};

void testDomain();