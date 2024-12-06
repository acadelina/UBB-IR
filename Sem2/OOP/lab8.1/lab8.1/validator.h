#pragma once
#include<string>
#include<vector>
#include<cassert>
#include"disciplina.h"
using namespace std;


class ValidationExceptions {
	vector <string> mesage;
public:
	ValidationExceptions(vector<string> msg) : mesage{ msg } {}
	string get_msj()
	{

		string mesj = "";
		for (const string msj : mesage)
			mesj = mesj + msj + "\n";
		return mesj;
	}
};

class Validator {
public:
	void validare(string denum, int ore, string tip, string prof)
	{
		vector<string> msg;
		if (ore < 0)
			msg.push_back("Numarul de ore trebuie sa fie pozitiv!\n");
		for (size_t i = 0; i < denum.size(); i++)
			if (isdigit(denum.at(i)))
				msg.push_back("Denumirea introdusa este incorecta!\n");

		/*for (size_t i = 0; i < prof.size(); i++)
			if (isdigit(prof.at(i)));
				//return 0;*/
		if (isupper(prof.at(0)) == 0)
			msg.push_back("Cadrul didactic este incorect!\n");
		if (msg.size() > 0)
		{
			throw ValidationExceptions(msg);
		}
	}
};

void testValidare();

