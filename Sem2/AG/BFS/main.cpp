#include <iostream>
#include<fstream>
#define inf 100000
using namespace std;
ifstream f("mat.txt");

int m[100][100],c[100],dist[100],parinte[100];
//BFS
//Distanta de la un varf la toate celelalte graf fara costuri
void bfs(int vf,int n)
{
    int coada[100];
    int in=0,sf=-1;//cu in si sf parcurgem coada creata pe parcursul bfs
    for(int i=1;i<=n;i++)
    {
        //setam toate nodurile ca fiind nevizitate

        dist[i]=inf;
        parinte[i]=-1;
    }

    dist[vf]=0;
    coada[++sf]=vf;
    while(in<=sf)
    {
        int curent=coada[in];//scoatem din coada un primul nod
        in++;
        for(int j=1;j<=n;j++)
        {
            if(m[curent][j]&&dist[j]==inf)
            {
                //parcurgem toate nodurile iar daca acestea nu au fost vizitate le adaugam in coada
                dist[j]=dist[curent]+1;
                parinte[j]=curent;
                coada[++sf]=j;
            }
        }
    }

}
int main()
{
    int n,m1;
    f>>n>>m1;
    for(int i=1;i<=m1;i++)
    {
        int x,y;
        f>>x>>y;
        m[x][y]=1;
    }
    bfs(1,n);
    for(int i=1;i<=n;i++)
        if(dist[i]!=inf)
        cout<<i<<":"<<dist[i]<<'\n';
}
