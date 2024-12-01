#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


int hashCode(TElem e)
{
	return abs(e);
}

//functia de dispersie
int Colectie::d(TElem e) const
{
	return hashCode(e) % m;
}

//0(n)
Colectie::Colectie() {
	m = INIT_SIZE;
	e = new Node[m];
	urm = new int[m];
	for (int i = 0; i < m; i++)
	{
		e[i].elem = NIL;
		e[i].frec = 0;
		urm[i] = -1;
	}
	primliber = 0;
	size = 0;
}

//caz defavorabil:O(n), primliber e ultima poz
//caz mediu:O(n)
void Colectie::actPrimLiber()
{
	primliber++;
	while (primliber < m && e[primliber].elem != NIL)
		primliber++;
}

//0(n)
void Colectie::redimAndRehash()
{
	int cap_noua = m * 2;
	auto new_elems = new Node[cap_noua];
	auto old_elems = new Node[m];
	int* urm_nou = new int[cap_noua];

	for (int i = 0; i < cap_noua; i++)
	{
		new_elems[i].elem = NIL;
		new_elems[i].frec = 0;
		urm_nou[i] = -1;
	}

	old_elems = e;
	e = new_elems;
	urm = urm_nou;
	primliber = 0;
	m = cap_noua;
	size = 0;

	for (int i = 0; i < m / 2; i++) {
		if (old_elems[i].elem != NIL) {
			for (int j = 0; j < old_elems[i].frec; j++)
				adauga(old_elems[i].elem);
		}
	}

	delete[] old_elems;

}

//caz favorabil:O(1)
//caz defavorabil:O(n^2),cazul in care apelam redimAndRehash
//caz mediu:O(n)
void Colectie::adauga(TElem elem) {
	//locatia de dispersie a cheii
	int i = d(elem);
	if (e[i].elem==NIL)	// pozitia este libera
	{
		++size;
		e[i].elem = elem;	// adaugam elementul
		e[i].frec=1;
		if (i == primliber)
			actPrimLiber();	// actualizam primLiber, daca este nevoie
		return;
	}
	
	int j = -1;	// j va retine pozitia precedenta lui i, pentru a putea reface inlantuirea
	// daca pozitia nu este libera
	while (i != -1)	// iteram pana gasim capatul inlantuirii
	{
		if (e[i].elem == elem)
		{
			++size;
			e[i].frec++;
			return;
		}
		j = i;
		i = urm[i];
	}

	if (primliber >= m)
	{
		redimAndRehash();
	}
	// adaugam elementul
	++size;
	e[primliber].elem = elem;
	e[primliber].frec=1;
	urm[j] =primliber;
	actPrimLiber();
	
}

//0(n)
bool Colectie::sterge(TElem elem) {
	
	int i = d(elem);
	int j = -1;
	int k = 0;
	while (urm[k] != i && k < m)
		k++;
	if (k != m)
		j = k;
	while (i != -1 && e[i].elem != elem) {
		j = i;
		i = urm[i];
	}
	if (i == -1)
		return false;

	if (e[i].frec > 1) {
		--e[i].frec;
	}
	else {
		bool found = false;
		do {
			int p = urm[i];
			int pp = i;
			while (p !=-1  && d(e[p].elem) != i) {
				pp = p;
				p = urm[p];
			}
			if (p == -1)
				found = true;
			else {
				e[i] = e[p];
				i = p;
				j = pp;
			}
		} while (!found);
		if (j != -1)
			urm[j] = urm[i];
		urm[i] = -1;
		e[i] = { NIL, 0 };
		if (primliber > i)
			primliber = i;
	}
	size--;
	return true;
	
}

//caz favorabil:O(1),elementul se afla pe pozitia returnata de d(elem)
//caz defavorabil:O(n),elementul se afla la capatul inlantuirii sau nu exista in tabela
//caz mediu:O(n)
bool Colectie::cauta(TElem elem)  {
	
	int i = d(elem);
	if (e[i].elem == NIL)
		return false;
	while (i != -1)	// iteram pana gasim capatul inlantuirii
	{
		//verificam daca elementul exista deja in tabela
		if (e[i].elem == elem) {
			return true;
		}
		i = urm[i];
	}
	return false;
}

//caz favorabil:O(1),elementul se afla pe pozitia returnata de d(elem)
//caz defavorabil:O(n),elementul se afla la capatul inlantuirii sau nu exista in tabela
//caz mediu:O(n)
int Colectie::nrAparitii(TElem elem) const {
	int i = d(elem);
	if (e[i].elem == NIL)
		return 0;
	while (i != -1)
	{
		//verificam daca elementul in tabela
		if (e[i].elem == elem) {
			return e[i].frec;
		}
		i = urm[i];
	}
	return 0;
}

//0(1)
int Colectie::dim() const {
	return size;
}

//0(1)
bool Colectie::vida() const {
	return size == 0;
	
}

//0(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//0(1)
Colectie::~Colectie() {
	delete[]e;
	delete[]urm;
}

//0(n),n-numarul de elemente din tabela de dispersie
int Colectie::transformaInMultime()
{
	int initSize = size;
	for (int i = 0; i < m; i++) {
		if (e[i].elem != NIL && e[i].frec > 1) {
			size -= (e[i].frec - 1); //se scade din dimensiunea totala numarul de dubluri-1
			e[i].frec = 1; //setam frecventa la 1
		}
	}
	return initSize - size;

}
