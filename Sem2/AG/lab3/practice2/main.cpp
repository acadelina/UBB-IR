#include <iostream>
#include<fstream>
#define inf 1000
using namespace std;
ifstream f("mat.txt");

int a[100][100],drum[100],parinte[100],rez[100];

void init(int n,int vf)
{
    for(int i=1;i<=n;i++)
    {
        drum[i]=inf;
        parinte[i]=-1;
    }
    drum[vf]=0;
}
void moore(int n,int vf)
{
    init(n,vf);
    int coada[100];
    int in,sf=-1;
    coada[++sf]=vf;
    while(in<=sf)
    {
        int u=coada[in++];
        for(int i=1;i<=n;i++)
        {
            if(a[u][i])
            {
                if(drum[i]>drum[u]+1)
                {
                    drum[i]=drum[u]+1;
                    parinte[i]=u;
                    coada[++sf]=i;
                }
            }
        }
    }
}
void drummore(int vf)
{
    int lg=drum[vf];
    while(vf!=-1)
    {
        rez[lg--]=vf;
        vf=parinte[vf];
    }
}
int main()
{
   int n,m,in,sf;
   f>>n>>m;
   for(int i=1;i<=m;i++)
   {
       int x,y;
       f>>x>>y;
       a[x][y]=1;
   }
   cin>>in>>sf;
   moore(n,in);
   drummore(sf);
   for(int i=0;i<=drum[sf];i++)
    cout<<rez[i]<<" ";
}
