#include <bits/stdc++.h>
using namespace std;
ifstream fin("in.txt");
ofstream fout("out.txt");
struct muchie{int x,y,cost,ver;}v[1001];
int n,m,i,j,l[101],auxi,auxj,nm,costAPM,x,y,c;
int main()
{
    fin>>n>>m;
    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        v[i].x=x;
        v[i].y=y;
        v[i].cost=c;
    }
    for(i=1;i<m;i++)
        for(j=i+1;j<=m;j++)
            if(v[i].cost>v[j].cost)
                swap(v[i],v[j]);
    for(i=1;i<=n;i++)
        l[i]=i;
    i=0;
    do{
        i++;
        if(l[v[i].x]!=l[v[i].y])
        {
            v[i].ver=1;
            nm++;
            costAPM+=v[i].cost;
            auxi=l[v[i].x];
            auxj=l[v[i].y];
            for(j=1;j<=n;j++)
                if(l[j]==auxj)
                    l[j]=auxi;
        }
    }while(nm<n-1);
    fout<<costAPM<<"\n";
    for(i=1;i<=m;i++)
        if(v[i].ver==1)
            fout<<v[i].x<<" "<<v[i].y<<"\n";
    return 0;
}
