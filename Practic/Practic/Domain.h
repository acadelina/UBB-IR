#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Task
{
	int id;
	string desc;
	string stare;
	vector<string> prog;
public:
	//constructorul clasei
	Task(int id, string desc, string stare, vector<string> prog) :id{ id }, desc{ desc }, stare{ stare }, prog{ prog } {};
	/*
	Getter pentru id
	postcond:id->int
	*/
	int getid()
	{
		return id;
	}
	/*
	Getter pentru descriere
	postcond:desc->string
	*/
	string getdesc()
	{
		return desc;
	}
	/*
	Getter pentru stare
	postcond:stare->string
	*/
	string  getstare()
	{
		return stare;
	}
	/*
	Getter pentru programatori
	postcond:prog->vector de int
	*/
	vector<string> getprog()
	{
		return prog;
	}

	/*
	Setter pentru stare
	postcond: n-string
	*/
	void setstare(string n)
	{
		this->stare = n;
	}
};

void testDomain();