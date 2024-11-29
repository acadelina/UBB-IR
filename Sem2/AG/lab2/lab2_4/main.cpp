#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;

ifstream f("matrice.txt");

int adiacent[100][100], dist[100], parinte[100];

void bfs(int s, int n)
{
    int coada[100];
    int in,sf=-1;
    coada[++sf]=s;
    dist[s]=0;
    parinte[s]=-1;
    while(in<=sf)
    {

        int u=coada[in++];
        for(int x=1;x<=n;x++)
            if(adiacent[u][x]&&dist[x]==-1)
        {

            dist[x]=dist[u]+1;
            parinte[x]=u;
            coada[++sf]=x;
        }
    }
}
int main()
{
    int n,m;
    f>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        f>>u>>v;
        adiacent[u][v]=1;
    }
    memset(dist, -1, sizeof(dist));
    memset(parinte, -1, sizeof(parinte));
    int s;
    f>>s;
    bfs(s,n);
    for(int i=1;i<=n;i++)
    {
        cout<<"Nodul "<<i<<": ";
        if(dist[i] == -1)
            cout<<"nedescoperit\n";
        else
            cout<<"distanta="<<dist[i]<<"\n";
    }
    return 0;
}
