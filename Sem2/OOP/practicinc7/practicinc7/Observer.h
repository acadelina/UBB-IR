#pragma once
#include<QtWidgets>
#include<vector>
#include<algorithm>
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
	void addobs(Observer* o)
	{
		obs.push_back(o);
	}
	void remobs(Observer* o)
	{
		obs.erase(remove(obs.begin(), obs.end(), o), obs.end());
	}

protected:
	void notify()
	{
		for (auto a : obs)
			a->update();
	}
};