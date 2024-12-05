#include <iostream>
#include<fstream>
#include<queue>
#include<vector>
#define inf 100000
using namespace std;

ifstream f("mat.txt");

int D[10000];
bool inC[10000];
vector<pair<int,int>>drum[10000];

struct comp
{
    bool operator()(int x,int y)
    {
        return D[x]>D[y];
    }
};
priority_queue<int,vector<int>,comp>coada;
void Di(int n,int vf)
{
    for(int i=0;i<n;i++)
        D[i]=inf;
    D[vf]=0;
    coada.push(vf);
    inC[vf]=true;
    while(!coada.empty())
    {
        int u=coada.top();
        coada.pop();
        inC[u]=true;

        for(int i=0;i<drum[u].size();i++)
        {
            int v=drum[u][i].first;
            int c=drum[u][i].second;
            if(D[u]+c<D[v])
            {
                D[v]=D[u]+c;
                if(inC[v]==false)
                {
                    coada.push(v);
                    inC[v]=true;
                }
            }
        }
    }
}
int main()
{
    int n,m,in;
    f>>n>>m>>in;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        drum[x].push_back(make_pair(y,z));
    }
    Di(n,in);
    for(int i=0;i<n;i++)
    {
        if(D[i]!=inf)
            cout<<D[i]<<" ";
        else
            cout<<"INF ";
    }
}
