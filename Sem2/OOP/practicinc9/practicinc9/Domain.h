#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Task {
	int id;
	string desc;
	vector<string> prog;
	string stare;
public:
	Task(int id, string desc, vector<string> prog, string stare) :id{ id }, desc{ desc }, prog{ prog }, stare{ stare } {};
	int getid()
	{
		return id;
	}
	string getdesc()
	{
		return desc;
	}
	vector<string> getprog()
	{
		return prog;
	}
	string getstare()
	{
		return stare;
	}
	void setstare(string n)
	{
		this->stare = n;
	}

};
void testDomain();