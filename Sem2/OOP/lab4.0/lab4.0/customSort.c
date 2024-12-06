#include "customSort.h"
#include "medicamenteService.h"


void sort(MyList* l, CompareFct cmpF) {
    int i, j;
    for (i = 0; i < l->lenght - 1; i++) {
        for (j = i + 1; j < l->lenght; j++) {
            if (cmpF((l->lista[i]), (l->lista[j])) > 0) {
                // Swap elements l->lista[i] and l->lista[j]
                medicament* temp = l->lista[i];
                l->lista[i] = l->lista[j];
                l->lista[j] = temp;
            }
        }
    }
}

void insertSort(MyList* l, CompareFct cmpF)
{
    for (int i = 1; i < l->lenght; i++)
    {
        int ind = i - 1;
        medicament* a = l->lista[i];
        while (ind >= 0 && cmpF(a, l->lista[ind]) < 0)
        {
            l->lista[ind + 1] = l->lista[ind];
            ind--;
        }
        l->lista[ind + 1] = a;
    }
}
void testSort() {
    // Create a test list
    ManagerMeds m = createManagerMeds();
    adaugareService(&m, 1, "Med1", 10, 50);
    adaugareService(&m, 2, "Med2", 5, 30);
    adaugareService(&m, 3, "Med3", 15, 20);

    // Define a comparison function (e.g., cmpStoc for sorting by stoc)


    // Sort the test list using the sort function
    sort(m.allMeds, cmpStoc);

    // Assert that the resulting list is sorted
    medicament* med = m.allMeds->lista[0];
    medicament* med1 = m.allMeds->lista[1];
    medicament* med2 = m.allMeds->lista[2];
    assert(med->cantitate == 20); // First element should have stoc 5
    assert(med1->cantitate == 30); // First element should have stoc 5
    assert(med2->cantitate == 50); // First element should have stoc 5

    // Clean up
    destroyManagerMeds(&m);

    ManagerMeds m1 = createManagerMeds();
    adaugareService(&m1, 1, "Med1", 10, 50);
    adaugareService(&m1, 2, "Med2", 5, 30);
    adaugareService(&m1, 3, "Med3", 15, 20);

    // Define a comparison function (e.g., cmpStoc for sorting by stoc)


    // Sort the test list using the sort function
    insertSort(m1.allMeds, cmpStoc);

    // Assert that the resulting list is sorted
    medicament* med0 = m1.allMeds->lista[0];
    medicament* med01 = m1.allMeds->lista[1];
    medicament* med02 = m1.allMeds->lista[2];
    assert(med0->cantitate == 20); // First element should have stoc 5
    assert(med01->cantitate == 30); // First element should have stoc 5
    assert(med02->cantitate == 50); // First element should have stoc 5

    destroyManagerMeds(&m1);

}