#pragma once

#include "disciplina.h"
//#include "observer.h"
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include"Observer.h"


using std::vector;
using std::shuffle;

class Contract:public Observable {
	vector <Disciplina> cont;

public:
	Contract();

	void addCont(const Disciplina& d) {
		this->cont.push_back(d);
	}

	void clearContract() {
		this->cont.clear();
	}

	void fillContract(size_t dimension, vector<Disciplina> all) {
		vector<Disciplina> all1;
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while ((this->cont.size() < dimension) && (all.size() > 0)) {
			this->cont.push_back(all.back());
			all1.push_back(all.back());
			all.pop_back();
			if (all.size() == 0 && cont.size() < dimension) {
				all = all1;
				all1.clear();
				std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
			}
		}
	}

	const vector <Disciplina>& getAllCont() {
		return this->cont;
	}



	~Contract() {};
};
void testContract();
