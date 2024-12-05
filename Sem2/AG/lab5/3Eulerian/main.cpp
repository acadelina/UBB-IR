#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("citire.txt");
ofstream fout("afisare.txt");
int n, m, a[100][100], L[100], p = 0;

void Euler(int k)
{
    for (int i = 0; i < n; i++)
        if (a[k][i] == 1)
        {
            a[k][i] = a[i][k] = 0;
            Euler(i);
        }
    L[++p] = k;
}
int main()
{
	int i, j, k;
	fin >> n >> m;
    for (k = 1; k <= m; k++)
    {
		fin >> i >> j;
		a[i][j] = a[j][i] = 1;
	}
	Euler(0);
	for (i = 1; i <p; i++)
		fout << L[i] << " ";
	return 0;
}



