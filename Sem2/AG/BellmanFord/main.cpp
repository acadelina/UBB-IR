#include <iostream>
#include<fstream>
#define inf 100000
using namespace std;
ifstream f("mat.txt");
int a[100][100],drum[100],parinte[100];
void init(int n,int vf)
{
    for(int i=0;i<n;i++)
    {
        drum[i]=inf;
        parinte[i]=-1;
    }
    drum[vf]=0;
}
void relax(int u,int v)
{
    if(drum[v]>drum[u]+a[u][v]&&drum[u]!=inf)
    {
        drum[v]=drum[u]+a[u][v];
        parinte[v]=u;
    }
}
void BF(int n,int vf)
{
    init(n,vf);
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(a[i][j])
                    relax(i,j);
    /*for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(a[i][j])
    {
        if(drum[j]>drum[i]+a[i][j]&&drum[i]!=inf)
            return false;
    }
    return true;*/
}
int main()
{
    int m,n,in;
    f>>n>>m>>in;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        a[x][y]=z;
    }

    BF(n,in);
    for(int i=0;i<n;i++)
        cout<<drum[i]<<" ";
    /*    cout<<"Costul drumului: "<<drum[sf]<<"\n";

        while(sf!=-1)
        {
            cout<<sf<<" ";
            sf=parinte[sf];

        }
    }*/

}

