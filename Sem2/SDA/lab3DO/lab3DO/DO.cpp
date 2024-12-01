#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

//0(1)
DO::DO(Relatie r) {
	
	this->start = NULL;
	this->stop = NULL;
	this->fct = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
//Complexitate :
// Best case: cheia headului nu este in relatie cu cheia primita => 0(1)
// Worst case : toate cheile sunt in relatie si elementul trebuie adaugat la final => 0(n)
// Average case : while se poate executa 1,2,3...n ori => 0(n)
// Overall : O(n)
TValoare DO::adauga(TCheie c, TValoare v) {
	
	Node* currentNode = start;

	// Cautăm poziția corectă pentru inserarea sau actualizarea cheii
	while (currentNode != stop && fct(currentNode->key.first, c)) {
		if (currentNode->key.first == c) {
			// Cheia există deja, înlocuim valoarea și returnăm vechea valoare
			TValoare oldValue = currentNode->key.second;
			currentNode->key.second = v;
			return oldValue;
		}
		currentNode = currentNode->next;
	}

	//caz pentru tail
	if (currentNode != nullptr && currentNode->key.first == c) {
		TValoare oldValue = currentNode->key.second;
		currentNode->key.second = v;
		return oldValue;
	}

	// Cream o nouă pereche (cheie, valoare)
	 
	Node* new_node = new Node;
	new_node->key = make_pair(c, v);
	new_node->next = nullptr;
	new_node->pre = nullptr;

	// Cazul în care lista este goală sau trebuie să inserăm la început
	if (start == nullptr || !fct(start->key.first, c)) {
		new_node->next = start;
		if (start != nullptr) {
			start->pre = new_node;
		}
		start = new_node;
		if (stop == nullptr) {
			stop = new_node;
		}
		return NULL_TVALOARE;
	}

	// Cazul în care trebuie să inserăm la sfârșit
	if (fct(stop->key.first, c)) {
		stop->next = new_node;
		new_node->pre = stop;
		stop = new_node;
		return NULL_TVALOARE;
	}


	// cazul in care trebuie sa inseram la mijloc
	Node* prevNode = currentNode->pre;
	new_node->next = currentNode;
	new_node->pre = prevNode;
	prevNode->next = new_node;
	currentNode->pre = new_node;

	return NULL_TVALOARE;
	
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//Complexitate:
// Best case : elementul cautat este primul => Theta(1)
// Worst case : elementul nu se afla in dictionar => Theta(n)
// Average case : 0(n)
// Overall: O(n)
TValoare DO::cauta(TCheie c) const {
	/* de adaugat */
	auto head = start;
	while (head != NULL)
	{
		if (head->key.first == c)
		{
			TValoare ret = head->key.second;
			return ret;
		}
		head = head->next;
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
// Complexitate:
// Best case : elementul cautat este headul => Theta(1)
// Worst case : elementul nu se afla in dictionar => Theta(n)
// Average case : T(n)= n+1/2 => Theta(n)
// Overall: O(n)
TValoare DO::sterge(TCheie c) {
	/* de adaugat */
	Node* curent = start;
	if (start == NULL) {
		return NULL_TVALOARE;
	}
	while (curent != nullptr)
	{
		if (curent->key.first == c)
		{
			if (curent == start)
			{
				TCheie ret = curent->key.second;
				start = curent->next;
				delete curent;
				return ret;
			}
			if (curent == stop)
			{

				TCheie ret = curent->key.second;
				stop = curent->pre;
				curent->pre->next = nullptr;
				delete curent;
				return ret;
			}
			TCheie ret = curent->key.second;
			curent->pre->next = curent->next;
			curent->next->pre = curent->pre;
			delete curent;
			return ret;
		}
		curent = curent->next;
	}
	return NULL_TVALOARE;


}
//0(n)
//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	/* de adaugat */
	int size = 0;
	Node* head = start;
	while (head != NULL)
	{
		head = head->next;
		++size;
	}
	return size;
}

//verifica daca dictionarul e vid
//0(1)
bool DO::vid() const {
	/* de adaugat */
	if (start == NULL)
		return true;
	return false;
}

//0(1)
Iterator DO::iterator() const {
	return  Iterator(*this);
}

//0(1)
DO::~DO() {
	/* de adaugat */
	auto head = start;
	Node* current = head;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

//0(n*m)-unde n este numarul de chei din dictionarul curent si m este numarul de chei din dictionarul dat
int DO::actualizeazaVal(DO& d)
{
	Node* curent = d.start;
	int nr = 0;
	while (curent != nullptr)
	{
		if (cauta(curent->key.first) != NULL_TVALOARE)
		{
			nr++;
			adauga(curent->key.first, curent->key.second);
		}
		curent = curent->next;
	}
	return nr;
}