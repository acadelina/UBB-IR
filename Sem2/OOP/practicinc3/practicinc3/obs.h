#pragma once
#include"vector"
#include"algorithm"
using namespace std;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable :public Observer
{
	vector<Observer*> obs;
public:
	void addObs(Observer* o)
	{
		obs.push_back(o);

	}
	void removeObs(Observer* o)
	{
		obs.erase(remove(obs.begin(), obs.end(), o), obs.end());
	}
protected:
	void notify()
	{
		for (auto o : obs)
			o->update();
	}
};