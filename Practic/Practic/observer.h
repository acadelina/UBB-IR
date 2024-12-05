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
	vector<Observer*> obs;
public:
	void addObs(Observer* o)
	{
		obs.push_back(o);
	}
	void rmObs(Observer* o)
	{
		obs.erase(remove(obs.begin(), obs.end(), o), obs.end());
	}
protected:
	void notify()
	{
		for (auto e : obs)
			e->update();
	}
};