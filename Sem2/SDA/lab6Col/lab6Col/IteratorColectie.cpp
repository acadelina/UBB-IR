#include "IteratorColectie.h"
#include "Colectie.h"

void IteratorColectie::deplasare()
{
	while ((curent < col.m) && col.e[curent].elem == NIL)
		curent++;
}
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
	frecventa = 1;
	deplasare();
}

void IteratorColectie::prim() {
	curent = 0;
	frecventa = 1;
	deplasare();
}


void IteratorColectie::urmator() {
	if (frecventa + 1 > col.e[curent].frec) {
		curent++;
		frecventa = 1;
		deplasare();
	}
	else {
		++frecventa;
	}
}


bool IteratorColectie::valid() const {
	
	return curent<col.m;
}



TElem IteratorColectie::element() const {
	return col.e[curent].elem;
}
