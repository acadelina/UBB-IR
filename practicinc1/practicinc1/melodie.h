#pragma once
#include<iostream>
using namespace std;
class Melodie {
	int id;
	string titlu;
	string artist;
	int rank;
public:
	Melodie(int id, string titlu, string artist, int rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {};
	int getid()
	{
		return this->id;
	}
	string gettitlu()
	{
		return this->titlu;
	}
	string getartist()
	{
		return this->artist;
	}
	int getrank()
	{
		return this->rank;
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

	void setrank(int n)
	{
		this->rank = n;
	}

};

void testDomain();