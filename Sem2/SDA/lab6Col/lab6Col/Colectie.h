#pragma once

#define NULL_TELEM -1
#define NIL -100000
#define MAX 10000
#define INIT_SIZE 1000
typedef int TElem;

class IteratorColectie;

struct Node {
	TElem elem;
	int frec;
	//Node* urm;
	
};
class Colectie
{
	friend class IteratorColectie;

private:
	int m,size;//m-numarul de locatii din tabela de dispersie,size-nr de elem
	Node* e;//vectorul elementelor
	int* urm;//vectorul legaturilor
	int primliber;//locatia primei poz libere

	void actPrimLiber();

	void redimAndRehash();

	int d(TElem e) const;

public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) ;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	//transformarea in multime
	int transformaInMultime();

	// destructorul colectiei
	~Colectie();

};

