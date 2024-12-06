#pragma once
#include"Melodie.h"
#include<string.h>
#include<vector>
class ValidationExceptions {
private:
	vector<string> mesaj;
public:
	ValidationExceptions(vector<string> mesaj):mesaj{mesaj}{}
	string get_msj()
	{
		string mfinal = "";
		for (string msj : mesaj)
			mfinal = mfinal + msj + "\n";
		return mfinal;
	}

};
class Validator
{
public:
	void validareProdus(string nume,string tip,int pret,string producator)
	{
		vector<string> mesaj;
		for (auto i : nume)
		{
			if (!isalpha(i))
			{
				mesaj .push_back( "Numele nu pooate contine decat litere\n");
				break;
			}
		}
		vector<string> tipuri = { "mancare","bautura","legume","fructe","altele" };
		int ok = 0;
		for (auto t : tipuri)
			if (t== tip)
				ok = 1;
		if(ok==0)
			mesaj.push_back("Tip invalid\n");
		if (pret <= 0)
			mesaj.push_back("Pretul trebuie sa fie un numar pozitiv");

	}
};