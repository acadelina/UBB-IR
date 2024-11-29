#include <iostream>
#include<fstream>
using namespace std;

ifstream f("in.txt");
ofstream g("out.txt");
//KRUSKAL
struct muchie{
int x,y,cost,ver;
}v[1001];

int n,m,l[101],nrm=0,costT=0,x,y,cost;
int main()
{
   f>>n>>m;
   for(int i=1;i<=m;i++)
   {
       f>>x>>y>>cost;
       v[i].x=x;
       v[i].y=y;
       v[i].cost=cost;
   }
   //sortare muchii crescator dupa cost
   for(int i=1;i<m;i++)
    for(int j=i+1;j<=m;j++)
        if(v[i].cost>v[j].cost)
            swap(v[i],v[j]);

    for(int i=1;i<=n;i++)
        l[i]=i;
    int i=0;
    do{
        i++;
        if(l[v[i].x]!=l[v[i].y])
        {

            v[i].ver=1;//muchia se afla in arborele min
            nrm++;
            costT+=v[i].cost;
            int auxi=l[v[i].x];
            int auxj=l[v[i].y];
            for(int j=1;j<=n;j++)
                if(l[j]==auxj)
                    l[j]=auxi;
        }
    }while(nrm<n-1);
    g<<costT<<"\n";
    for(i=1;i<=m;i++)
        if(v[i].ver==1)
            g<<v[i].x<<" "<<v[i].y<<"\n";
    return 0;

}
