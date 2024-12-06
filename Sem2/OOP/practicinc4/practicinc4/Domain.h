#pragma once
#include<vector>
#include<iostream>
using namespace std;

class Task {
	int id;
	string desc;
	vector<string> prog;
	string stare;
public:
	Task(int id, string desc, vector<string> prog, string stare) :id{ id }, desc{ desc }, prog{ prog }, stare{ stare } {};
	void setid(int n)
	{
		this->id = n;
	}
	void setdesc(string n)
	{
		this->desc= n;
	}

	void setprog(vector<string> p)
	{
		this->prog = p;
	}

	void setstare(string n)
	{
		this->stare = n;
	}

	int getid()
	{
		return this->id;
	}

	string getdesc()
	{
		return this->desc;
	}
	vector<string> getprog()
	{
		return this->prog;
	}
	string getstare()
	{
		return this->stare;
	}
};

void testDomain();