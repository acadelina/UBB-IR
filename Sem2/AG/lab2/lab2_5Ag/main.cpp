#include <iostream>
#include <fstream>
using namespace std;
ifstream in("graf.txt");
void dfs(int nod, int nrNoduri, int vizitat[], int matAd[100][100])
{
    vizitat[nod] = 1;
    for (int i=1; i <= nrNoduri; i++)
        if (matAd[nod][i]==1 && vizitat[i]==0)
        {
            cout<<i<<' ';
            dfs(i, nrNoduri, vizitat, matAd);
        }
}

void citesteGraf(int &nrNoduri, int &nrMuchii, int matAd[100][100])
{
    int x, y;
    in >> nrNoduri >> nrMuchii;
    for (int i = 1; i <= nrMuchii; i++)
    {
        in>>x>>y;
        matAd[x][y] = matAd[y][x] = 1;
    }
}

void initVizitat(int vizitat[])
{
    for (int i = 1; i < 100; i++)
        vizitat[i] = 0;
}

int main()
{
   int nrNoduri, nrMuchii, vizitat[100], matAd[100][100];
   citesteGraf(nrNoduri, nrMuchii, matAd);
   initVizitat(vizitat);
   dfs(1, nrNoduri, vizitat, matAd);
    return 0;
}
