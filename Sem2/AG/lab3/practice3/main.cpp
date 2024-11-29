#include <iostream>
#include<fstream>
#include<vector>
#define inf 10000000
using namespace std;
ifstream f("mat.txt");

int a[1000][1000],drum[1000],parinte[1000],vizitat[1000];


void init(int n,int vf)
{
    for(int i=0;i<n;i++)
    {
        if(a[vf][i]==0)
            drum[i]=inf;
        else
            drum[i]=a[vf][i];
        parinte[i]=-1;

    }
    drum[vf]=0;
    parinte[vf]=0;
}

void relax(int u,int v)
{
    if(drum[v]>drum[u]+a[u][v]&&drum[u]!=inf)
    {
        drum[v]=drum[u]+a[u][v];
        parinte[v]=u;
    }
}

int ExtractMin(int n)
{
    int mi=inf,j;
    for(int i=0;i<=n;i++)
    {
        if(drum[i]<mi&&vizitat[i]==0)
        {
            mi=drum[i];
            j=i;
        }
    }

    return mi;
}

void Dijkstra(int n,int vf)
{


    init(n,vf);
    drum[-1]=inf;
    for(int j=0;j<n;++j)
    {
        int pm=-1;
        for(int x=0;x<n;++x)
            if(parinte[x]==-1&&drum[x]<drum[pm])
                    pm=x;

        if(pm>-2)
        {
            parinte[pm]=0;
            for(int k=0;k<n;++k)
                if(parinte[k]==0&&drum[k]>drum[pm]+a[pm][k])
                        drum[k]=drum[pm]+a[pm][k];
        }
       /* int u=ExtractMin(n);
        vizitat[u]=1;
        for(int i=0;i<n;i++)
        {
            if(a[u][i]&&vizitat[i]==0&&drum[u]!=inf)
                relax(u,i);
        }
    }*/
}}
int main()
{
    int n,m,in;
    f>>n>>m>>in;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        a[x][y]=z;
    }

    Dijkstra(n,in);
    for(int i=0;i<n;i++)
    {
        if(drum[i]!=inf)
        {
            cout<<"Drum "<<i<<": "<<drum[i]<<"\n";

        }
        else
        {
            cout<<"Nu exista drum la varful: "<<i<<"\n";
        }
    }
}
