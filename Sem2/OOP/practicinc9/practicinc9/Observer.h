#pragma once
#include<vector>
using namespace std;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
	vector<Observer*> v;
public:
	Observable() = default;
	void addObs(Observer* o)
	{
		v.push_back(o);
	}
	void rmObs(Observer* o)
	{
		v.erase(remove(v.begin(), v.end(), o), v.end());
	}
protected:
	void notify()
	{
		for (auto a : v)
			a->update();
	}
};