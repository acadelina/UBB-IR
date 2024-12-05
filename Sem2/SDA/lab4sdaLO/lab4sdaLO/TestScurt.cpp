#include <assert.h>
#include<iostream>
using namespace std;
#include "Iterator.h"
#include "LO.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator iterator = lo.iterator();
    assert(iterator.valid());
    iterator.prim();
    assert(iterator.element() == 1);
    assert(iterator.elimina() == 1);
    assert(!iterator.valid());
    lo.adauga(1);
    iterator.prim();
    assert(iterator.valid());
    assert(lo.cauta(1) == 0);
    assert(lo.sterge(0) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());

    LO lo2 = LO(relatie1);
    for (int i = 1; i <=11; i++)
        lo2.adauga(i);
    //cout << lo2.cauta(1) << " " << lo2.cauta(2) << " " << lo2.cauta(5) << "\n";
    assert(lo2.eliminaDinkink(3) == 3);
    try {
        lo2.eliminaDinkink(5);
        assert(false);
    }
    catch (const exception&)
    {
        assert(true);
    }


}
