#pragma once
#include<iostream>
using namespace std;

class Melodie {
	int id;
	string titlu;
	string artist;
	string gen;
public:
	Melodie(int id,string titlu,string artist,string gen):id{id},titlu{titlu},artist{artist},gen{gen}{}
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