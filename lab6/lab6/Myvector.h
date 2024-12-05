#pragma once
#include<memory>
#include<iostream>
#include "disciplina.h"

template<typename Disciplina>
class IteratorVectoor;
template<typename Disciplina>


class Myvector
{
	
public:
	//constructor
	Myvector(); 
	//copy constructor
	Myvector(const Myvector& ot);
	//destructor
	~Myvector();
	
	
	

	//operator de atribuire
	Myvector& operator = ( Myvector&& ot)noexcept;

	
	//functie de add
	void add(const Disciplina& el);

	//functie de stergere
	void remove(int poz);

	//functie de get
	Disciplina& get(int poz) const;

	//fuctie de atribuire
	void set(int poz, const Disciplina& el);

	//dimensiunea
	int size() const noexcept;


	//functie de sortare
	void sort(const int mod, const char& field);

	friend class IteratorVectoor<Disciplina>;
	//functii care creeaza iteratori
	IteratorVectoor<Disciplina> begin();
	IteratorVectoor<Disciplina> end();
private:
	//capacitatea vectorului
	int cap;
	//lungimea curenta
	int lg;
	//pointer la vectorul de discipline
	Disciplina* elems;
	//functie care aloca spatiu
	void ensureCapacity();
	
};

//constructor
template<typename Disciplina>
Myvector<Disciplina>::Myvector() : cap{ 2 }, lg{ 0 }, elems{ new Disciplina[2] } {};

//constructor de copiere
template<typename Disciplina>
Myvector<Disciplina>::Myvector(const Myvector<Disciplina>& ot)
{
	elems = new Disciplina[ot.cap];
	for (int i = 0; i < ot.lg; i++)
		if(i<ot.cap)
			elems[i] = ot.elems[i];
	cap = ot.cap;
	lg = ot.lg;
	
}

//destructor
template<typename Disciplina>
Myvector<Disciplina>::~Myvector()
{
	delete[] elems;
}

//move contructor
template<typename Disciplina>
Myvector<Disciplina>& Myvector<Disciplina>::operator=( Myvector<Disciplina>&& ot) noexcept
{
	delete[]elems;
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

//adaugare elem
template<typename Disciplina>
void Myvector<Disciplina>::add(const Disciplina& d)
{
		ensureCapacity();
		elems[lg++] = d;
}

//stergere elem
template<typename Disciplina>
void Myvector<Disciplina>::remove(int poz)
{
	for (auto i = poz; i < lg - 1; i++)
		elems[i] = elems[i + 1];
	lg--;
}

//get elem
template<typename Disciplina>
Disciplina& Myvector<Disciplina>::get(int poz)const {
	return elems[poz];
}

//setare elem
template<typename Disciplina>
void Myvector< Disciplina>::set(int poz, const Disciplina& el)
{
	elems[poz] = el;
}

//dimensiunea vectorului
template<typename Disciplina>
int Myvector< Disciplina>::size()const noexcept
{
	return lg;
}

template<typename Disciplina>
void Myvector<Disciplina>::ensureCapacity() {
	if (lg < cap)
		return;
	cap *= 2;
	Disciplina* aux = new Disciplina[cap];
	for (int i = 0; i < lg; i++)
		aux[i] = elems[i];
	delete[] elems;
	elems= aux;

}

//functie de comparare
inline int cmpF(int mode, const char& field, const Disciplina& D1, const Disciplina& D2)
{
	if (field == 'd') //dupa denumire
	{
		if (mode == 0) //crescator
			return D1.getDenum() >D2.getDenum();
		else
			return D1.getDenum() < D2.getDenum();
	}

	if (field == 'o') // sortam dupa ore
	{
		if (mode == 0) // sortam crescator
			return D1.getOre() > D2.getOre();
		else
			return D1.getOre() < D2.getOre();
	}


	if (mode == 0) // sortam crescator
		if (D1.getProf() == D2.getProf())
			return D1.getTip() > D2.getTip();
		else
			return D1.getProf() > D2.getProf();
	else
		if (D1.getProf() == D2.getProf())
			return D1.getTip() < D2.getTip();
		else
			return D1.getProf() < D2.getProf();

}

//functie de sortare
template<typename Disciplina>
void Myvector<Disciplina>::sort(int mode, const char& field)
{
	int ok = 0;
	while (!ok)
	{
		ok = 1;
		for(int i=0;i<lg-1;i++)
			if (cmpF(mode, field, elems[i], elems[i + 1]))
			{
				swap(elems[i], elems[i + 1]);
				ok = 0;
			}
	}
}


template<typename Disciplina>
IteratorVectoor<Disciplina> Myvector<Disciplina>::begin()
{
	return IteratorVectoor<Disciplina>(*this);
}

template<typename Disciplina>
IteratorVectoor<Disciplina> Myvector<Disciplina>::end()
{
	return IteratorVectoor<Disciplina>(*this, lg);
}

template<typename Disciplina>
class IteratorVectoor {
private:
	const Myvector<Disciplina>& v;
	int poz = 0;
public:
	//constructorul clasei
	IteratorVectoor(const Myvector<Disciplina>& v) noexcept;
	//constructoe
	IteratorVectoor(const Myvector<Disciplina>& v, int poz)noexcept;
	//validarea iteratorului
	bool valid()const;
	//getter pt elementul curent
	Disciplina& element() const;
	//trecerea la urmatorul elem
	void next();

	//returneaza elementul []
	Disciplina& operator*();
	//overload operator++
	IteratorVectoor& operator++();
	//overload operator++
	bool operator==(const IteratorVectoor& ot)noexcept;
	//overload operator!=
	bool operator!=(const IteratorVectoor& ot)noexcept;
};


//constructor
template<typename Disciplina>
IteratorVectoor<Disciplina>::IteratorVectoor(const Myvector<Disciplina>& v) noexcept :v{ v } {}


template<typename Disciplina>
IteratorVectoor<Disciplina>::IteratorVectoor(const Myvector<Disciplina>& v, int poz)noexcept : v{ v }, poz{ poz } {}

//validarea dimensiunii vectorului
template<typename Disciplina>
bool IteratorVectoor<Disciplina>::valid()const {
	return poz < v.lg;
}

//returnarea elementului de pe poz
template<typename Disciplina>
Disciplina& IteratorVectoor<Disciplina>::element() const {
	return v.elems[poz];
}

//element urmator
template<typename Disciplina>
void IteratorVectoor<Disciplina>::next() {
	poz++;
}


template<typename Disciplina>
Disciplina& IteratorVectoor<Disciplina>::operator*() {
	return element();
}

template<typename Disciplina>
IteratorVectoor<Disciplina>& IteratorVectoor<Disciplina>::operator++() {
	next();
	return *this;
}

template<typename Disciplina>
bool IteratorVectoor<Disciplina>::operator==(const IteratorVectoor<Disciplina>& ot) noexcept {
	return poz == ot.poz;
}

template<typename Disciplina>
bool IteratorVectoor < Disciplina > ::operator!=(const IteratorVectoor<Disciplina>& ot)noexcept {
	return !(*this == ot);
}
