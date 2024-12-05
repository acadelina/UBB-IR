#include <iostream>
#include<fstream>
#define inf 10000
using namespace std;
ifstream f("mat.txt");

int a[100][100],lg[100],p[100],rez[100];
void Moore(int n,int vf)
{
    //bfs
    for(int i=1;i<=n;i++)
        lg[i]=inf;
    lg[vf]=0;
    int coada[100];
    int in=0,sf=-1;
    coada[++sf]=vf;
    while(in<=sf)
    {
        int u=coada[in++];
        for(int i=1;i<=n;i++)
        {
            if(a[u][i])
            {
                if(lg[i]==inf)
                {
                    p[i]=u;
                    lg[i]=lg[u]+1;
                    coada[++sf]=i;
                }
            }
        }
    }


}
void Moore_drum(int vf)
{
    //se construieste rezultatul
    int k=lg[vf];//lungimea drumului
    rez[k]=vf;//se pun de la dreapta la stanga parintii incepand de la vf
    while(k>0)
    {
        rez[k-1]=p[rez[k]];
        k--;
    }
}
int main()
{
    int m,n,in,sf;
    f>>n>>m;
    for(int i=1;i<=m;i++)
    {

        int x,y;
        f>>x>>y;
        a[x][y]=1;
    }
    cin>>in>>sf;
    Moore(n,in);
    Moore_drum(sf);
    for(int i=0;i<=lg[4];i++)
    {
        cout<<rez[i]<<" ";
    }
}
