#pragma once
#include"Domain.h"

class ValError {
	string msg;
public:
	ValError(string msg) :msg{ msg } {};
	string getmsg()
	{
		return msg;
	}
};

class Validator
{
public:
	void validare( string nume, double pret)
	{
		string msg = "";
		if (nume == "")
			msg += "Numele nu poate fi vid\n";
		if (pret < 0 || pret>100)
			msg += "Pret invalid\n";
		if (msg != "")
			throw ValError(msg);
	}
};