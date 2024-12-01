#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	/* de adaugat */
	curent = dict.start;
}

void Iterator::prim() {
	/* de adaugat */
	curent = dict.start;
}

void Iterator::urmator() {
	/* de adaugat */
	curent = curent->next;
}

bool Iterator::valid() const {
	/* de adaugat */
	if (curent == NULL)
		return false;
	return true;
}

TElem Iterator::element() const {
	/* de adaugat */
	return pair <TCheie, TValoare>(curent->key.first, curent->key.second);
}


