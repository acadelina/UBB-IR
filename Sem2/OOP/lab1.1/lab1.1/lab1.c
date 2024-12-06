#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



void meniu()
{
    /*
    Functie care afiseaza meniul
    preconditii:
    postconditii:
    */
    printf("MENIU: \n");
    printf("1->Descompunere in suma de numere consecutive \n");
    printf("2->Descompunere in factori primi \n");
    printf("0->Iesire. \n");
}
void factori_primi(int n)
{
    /*
    Functie care afiseaza factorii primi ai unui numar natural nenul n
    preconditii: n-int,n>0
    postconditii:
    */
    int a = 2, p;
    while (n > 1)
    {
        p = 0;
        while (n % a == 0)
        {
            n /= a;
            p++;

        }
        if (p>0)
            printf("%d la puterea %d ;", a, p);
        a++;
    }
    printf("\n");

}
void suma(int a[100][100], int n, int* l, int* c)
{
    /*
    Functie care creeaza o matricefosrmata din liste cu numerele consecutive care adunate dau n
    preconditii: a-array
                 n-int
                 l-int
                 c-int
    postconditii: 
    */
    int s = 0, i = 0, j = 0;
    int m = 0, m2 = 0;
    for (i = 0; i < n; i++)
    {
        s = i;
        for (j = i + 1; j <= n && s < n; j++)
            s += j;
        if (s == n )
        {
            
            m2 += 1;
            for (int x = i; x < j; x++)
            {
                a[m][m2] = x;
               
                m2 = m2 + 1;
            }
            a[m][0] = m2;
            m = m + 1;
            m2 = 0;
        }
    }
    *l = m;
    *c = m2;
}
void afisare(int a[100][100], int l, int c)
{
   /*
   Functie care afiseaza sumele
   preconditii:a-array
               l-int
               c-int
   postconditii:
   */
    if (l == 0)
        printf("Numarul nu poate fi scris ca suma de numere consecutive \n");
    for (int i = 0; i < l; i++)
    {
        for (int j = 1; j < a[i][0]; j++)
            if (j<a[i][0]-1)
                printf("%d + ", a[i][j]);
            else 
                printf("%d \n", a[i][j]);

    }
}
int main()
{
    meniu();
    int cmd = 1;
    int n = 0, l = 0, c = 0;
    int a[100][100];
    scanf("%d", &cmd);

    while (cmd != 0)
    {
        if (cmd == 1)
        {
            printf("Dati numarul: \n");
            scanf("%d", &n);
            suma(a, n, &l, &c);
            afisare(a, l, c);
        }
        else
        {
            printf("Dati numarul: \n");
            scanf("%d", &n);
            factori_primi(n);
        }



        meniu();
        scanf("%d", &cmd);
    }

    return 0;
}
