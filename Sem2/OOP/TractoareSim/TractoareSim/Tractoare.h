#pragma once
#include<iostream>
using namespace std;

class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int roti;
public:
	Tractor(int id,string denumire,string tip,int roti):id{id},denumire{denumire},tip{tip},roti{roti}{}
	Tractor() :id{ 0 }, denumire{ "" }, tip{ "" }, roti{ 0 } {};
	int getId()
	{
		return this->id;
	}
	string getDenum()
	{
		return this->denumire;
	}

	string getTip()
	{
		return this->tip;
	}

	int getRoti()
	{
		return this->roti;
	}

	void setId(int n)
	{
		this->id = n;
	}

	void setDenum(string n)
	{
		this->denumire = n;
	}

	void setTip(string n)
	{
		this->tip = n;
	}

	void setRoti(int n)
	{
		this->roti = n;
	}
};

void testDomain();