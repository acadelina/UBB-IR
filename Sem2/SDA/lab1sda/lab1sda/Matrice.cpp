#include "Matrice.h"

#include <exception>
#include<iostream>

using namespace std;


//0(n)
void Matrice::redim() {
	//dublam capacitatea
	capacitate = capacitate * 2;

	//alocam spatiu de capacitate dubla
	TElem* enou1 = new int[capacitate];
	TElem* enou2 = new int[capacitate];

	//copiem valorile in spatiul nou
	for (int i = 0; i < dim; i++)
	{
		enou1[i] = v_col[i];
		enou2[i] = valoare[i];
	}

	//eliberam vechea zona
	delete[] v_col;
	delete[] valoare;

	//cei doi vectori indica spre zona noua
	v_col = enou1;
	valoare = enou2;

}



//0(n)
Matrice::Matrice(int m, int n) {
	
	if (m<=0 || n<=0)
	{
		throw std::exception("Numarul de linii si cel de coloane nu este pozitiv!");
	}
	else
	{
		//setam dimensiunile
		linii = m;
		coloane = n;
		dim = 0;
		
		//alocam spatiu de memorare
		v_col = new TElem[capacitate];
		v_lin = new TElem[linii + 1];
		valoare = new TElem[capacitate];

		//initializam vectorii
		for (int i = 0; i <= linii; i++)
			v_lin[i] = 0;
		for (int i = 0; i <= capacitate; i++)
		{
			v_col[i] = NULL_TELEMENT;
			valoare[i] = NULL_TELEMENT;
		}

	}
	
}

//0(1)
int Matrice::nrLinii() const{
	
	return linii;
}

//0(1)
int Matrice::nrColoane() const{
	
	return coloane;
}

//caz favorabil: O(1), daca pe linia data exista doar acel element nenul sau toate elementele de pe linie sunt nenule
//caz defavorabil: O(n), daca toate elementele de pe linie sunt nenule si j este ultima coloana
//caz mediu:O(n)
TElem Matrice::element(int i, int j) const{
	
	if (i < 0 || j < 0 || i >= linii || j >= coloane)
		throw std::exception("Indici invalizi!");
	else
	{
		//int nr_elem = v_lin[i + 1] - v_lin[i];
		
		for (int x = v_lin[i]; x < v_lin[i+1]; x++)
			if (v_col[x] == j)
			{
				return valoare[x];

			}
		return NULL_TELEMENT;
		
	}
}


//caz favorabil:O(1) cand pe linie nu exista nici un element si e=NULL_TELEM
//caz defavorabil:O(n) cand pe poz i j este element null si vrem sa il punem pe e sau cand e este null si practic il stergem; n-nr de elem de pe linie
//caz mediu: O(n)
TElem Matrice::modifica(int i, int j, TElem e) {
	TElem vechi;
	if (i < 0 || j < 0 || i >= linii || j >= coloane)
		throw std::exception("Indici invalizi!");
	else
	{
		int k;
		int ok = 0;
		for (k = v_lin[i]; k < v_lin[i + 1]; k++)
		{
			ok = 1;
			if (v_col[k] >= j)
				break;
		}

		if (ok && v_col[k] == j)
		{
			vechi = valoare[k];
			if (e == NULL_TELEMENT)
			{
				for (int x = i; x < linii; x++)
					v_lin[x]--;
				for (int x = k; x < dim; ++x)
				{
					v_col[x] = v_col[x + 1];
					valoare[x] = valoare[x + 1];
				}
				dim--;

			}
			else
			{
				valoare[k] = e;
			}
			return vechi;
		}
		if (e != NULL_TELEMENT)
		{
			if (dim == capacitate)
				redim();
			for (int x = dim; x > k; --x)
			{
				v_col[x] = v_col[x - 1];
				valoare[x] = valoare[x - 1];
			}
			v_col[k] = j;
			valoare[k] = e;
			dim++;
			for (int x = i + 1; x <= linii; x++)
				v_lin[x]++;
		}
		return NULL_TELEMENT;
		
	}
	

}

//0(linii*coloane*n),n-nr de elem de pe linie=>0(n^3)
Matrice Matrice:: transpusa()
{
	Matrice tr(coloane, linii);
	for (int i = 0; i < linii; ++i)
		for (int j = 0; j < coloane; ++j)
			tr.modifica(j, i, element(i, j));
	return tr;
}

