#pragma once
#include<vector>
#include<algorithm>
using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable  {
	vector<Observer*> obs;
public:
	void addObs(Observer* o)
	{
		obs.push_back(o);
	}
	
	void notify()
	{
		for (auto& a : obs)
			a->update();
	}
};