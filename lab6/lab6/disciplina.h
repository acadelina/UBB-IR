#pragma once
#include<string>
#include<iostream>
using namespace std;

class Disciplina {
	string denumire;
	int ore;
	string tip;
	string prof;

public:
	
	Disciplina(const string denum, int ore, const string tip,const string prof):denumire{denum},ore{ore},tip{tip},prof{prof}{}
	
	Disciplina() :denumire{ "" }, ore{ 0 }, tip{ "" }, prof{ "" } {};
	

	string getDenum() const {
		return denumire;
	}

	int getOre() const {
		return ore;
	}

	string getTip() const {
		return tip;
	}

	string getProf() const {
		return prof;
	}

	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, prof{ ot.prof } {
		cout << "*\n";
	}

	Disciplina& operator=(const Disciplina& ot)
	{
		denumire = ot.getDenum();
		tip = ot.getTip();
		ore = ot.getOre();
		prof = ot.getProf();
		return *this;
	}

	Disciplina(Disciplina&& source)noexcept
	{
		denumire = source.getDenum();
		tip = source.getTip();
		ore = source.getOre();
		prof = source.getProf();
	}
		
};

void testDomain();