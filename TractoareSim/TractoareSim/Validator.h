#pragma once
#include"Tractoare.h"
#include<vector>



class ValException {
private:
	string msj;
public:
	ValException(string msj) :msj{ msj } {}
	string getMsj()
	{
		return this->msj;
	}
};
class Validator {
public:
	void valideaza(int id, string denum, string tip, int roti) {
		string msj="";
		if (denum == "")
			msj+="Denumirea nu poate fi vida!\n";
		if (tip == "")
			msj+="Tipul nu poate fi vid!\n";
		if (roti % 2 == 1 || roti < 2 || roti>16)
			msj+="Rotile trebuie sa fie un numar par intre 2 si 16!\n";
		if (msj != "")
			throw ValException(msj);
	}

};
