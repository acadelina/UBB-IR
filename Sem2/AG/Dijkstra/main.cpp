#include <iostream>
#include<fstream>
#define inf 10000
#include<vector>
#include<queue>
using namespace std;
ifstream f("mat.txt");

int a[1000][1000],drum[1000],parinte[1000];
bool inCoada[1000];
vector<pair<int,int>> d;
struct comp{
    bool operator()(int x,int y)
    {
        return drum[x]>drum[y];
    }
};
priority_queue<int, queue<int>,comp> coada;
void init(int n,int vf)
{
    for(int i=0;i<n;i++)
    {
        drum[i]=inf;

    }
    drum[vf]=0;
}
/*int extract_min()
{
    int mini=inf,j;
    for(int i=0;i<coada.size();i++)
        if(coada[i]<mini)
            {mini=coada[i];
             j=i;}
    coada.erase(coada.begin()+j-1);
    return mini;
}
void relax(int u,int v)
{
    if(drum[v]>drum[u]+a[u][v]&&drum[u]!=inf)
    {
        drum[v]=drum[u]+a[u][v];
        parinte[v]=u;
    }

}
*/
void Dijkstra(int n,int vf)
{
    init(n,vf);
    coada.push(vf);
    inCoada[vf]=true;
    while(!coada.empty())
    {
        int u=coada.top();
        coada.pop();
        inCoada[u]=false;

        for(unsigned i=0;i<d[u].size();i++)
        {
            int v=d[u][i].first;
            int c=d[u][i].second;
            if(drum[u]+c<drum[v])
            {
                d[v]=d[u]+c;
                if(inCoada[v]==false)
                {
                    coada.push(v);
                    inCoada[v]=true;
                }
            }
        }
    }
  /*  for(int i=0;i<n;i++)
        coada.push_back(i);
    std::vector<int> s;
    while(coada.size())
    {
        int u=extract_min();
        s.push_back(u);
        for(int i=0;i<n;i++)
            if(a[u][i])
                relax(u,i);
    }*/
}
int main()
{
    int n,m,in;
    f>>n>>m>>in;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        d[x].push_back(make_pair(y,z));
    }

    Dijkstra(n,in);
    for(int i=0;i<n;i++)
    {
        if(drum[i]!=inf)
        {
            cout<<"Drum "<<i<<": "<<drum[i]<<"   :";

        }
        else
        {
            cout<<"Nu exista drum la varful: "<<i<<"\n";
        }
    }
}
