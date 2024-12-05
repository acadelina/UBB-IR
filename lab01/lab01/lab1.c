#include <stdio.h>
#include <stdlib.h>



void meniu()
{
    printf("1->Dati un numar n \n");
    printf("0->Iesire. \n");
}
void suma(int a[][100], int n, int* l, int* c)
{
    int s = 0, i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        s = i;
        for (j = i + 1; j <= n && s < n; j++)
            s += j;
        if (s == n)
        {
            *c += 1;
            for (int x = i; x <= j; j++)
            {
                a[*l][*c] = x;
                *c++;
            }
            a[*l][0] = *c;
            *l++;
        }
    }
}
void afisare(int a[][100], int l, int c)
{
    for (int i = 0; i <= l; i++)
    {
        for (int j = 1; j <= a[i][0]; j++)
            printf("%d + ", a[i][j]);
        printf("\n");
    }
}
int main()
{
    meniu();
    int cmd = 1;
    int n = 0, l = 0, c = 0;
    int a[100][100];
    scanf("%d", &cmd);

    while (cmd == 1)
    {
        printf("Dati numarul: \n");
        scanf("%d", &n);
        suma(a, n, &l, &c);
        afisare(a, l, c);



        meniu();
        scanf("%d", &cmd);
    }

    return 0;
}
