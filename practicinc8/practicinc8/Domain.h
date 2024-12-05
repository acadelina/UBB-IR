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
	//getter id
	int getid()
	{
		return id;
	}
	//getter titlu
	string gettitlu()
	{
		return titlu;
	}
	//getter de artist
	string getartist()
	{
		return artist;
	}
	//getter de rank
	int getrank()
	{
		return rank;
	}
	//setter rank
	//postcond:n-int
	void setrank(int n)
	{
		this->rank = n;
	}

	void settitlu(string n)
	{
		this->titlu = n;
	}
};

void testDomain();