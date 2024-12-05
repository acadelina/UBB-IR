#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#define inf 100000
using namespace std;
ifstream f("matrice.txt");
int D[1000],P[1000],rez[1000];
bool inc[1000];
vector<pair<int,int>>mat[1000];
struct comp{
    bool operator()(int x,int y)
    {
        return D[x]>D[y];
}};

priority_queue<int,vector<int>,comp>coada;

void dijkstra(int n,int vf)
{
    for(int i=0;i<n;i++)
    {
        D[i]=inf;
        P[i]=-1;
    }
    D[vf]=0;
    coada.push(vf);
    inc[vf]=true;
    while(!coada.empty())
    {
        int u=coada.top();
        coada.pop();
        for(int i=0;i<mat[u].size();i++)
        {
            int v=mat[u][i].first;
            int c=mat[u][i].second;
            if(D[v]>D[u]+c&&D[u]!=inf)
            {
                D[v]=D[u]+c;
                P[v]=u;
                if(inc[v]==false)
                {
                    coada.push(v);
                    inc[v]=true;
                }
            }
        }
    }

}
int main()
{
    int n,m,in,sf;
    f>>n>>m>>in>>sf;
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        mat[x].push_back(make_pair(y,z));

    }
    dijkstra(n,in);
    int k=sf,i=0;
    while(k!=-1)
    {
        rez[i]=k;
        k=P[k];
        i++;
    }

    cout<<"Costul drumului de la "<<in<<" la "<<sf<<": "<<D[sf]<<"\n";
    cout<<"Drumul de la "<<in<<" la "<<sf<<": ";
    for(int j=i-1;j>=0;j--)
        cout<<rez[j]<<" ";

}
