#pragma once
#ifndef  CUSTOMSORT_H_
#define CUSTOMSORT_H_
#include "MyList.h"

/*
* Tipul de functie pentru compararea a doua elemente
* returneaza 0 daca sunt egale, 1 daca el1>el2, -1 altfel
*/
typedef int (*CompareFct)(medicament* el1, medicament* el2);

/*
* Sorteaza o lista data cu selectin sort
* @param l: lista care se sorteaza
* @param cmpF: functia (relatia) dupa care se sorteaza
*
* post: lista l este sortata
*/
void sort(MyList* l, CompareFct cmpF);

void insertSort(MyList* l, CompareFct cmpF);

void testSort();
#endif // ! CUSTOMSORT_H_
