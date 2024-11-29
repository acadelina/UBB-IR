#include <iostream>
#include<fstream>
#define inf 11000
using namespace std;
ifstream f("mat.txt");

int a[100][100],drum[100],parinte[100];
void init(int n,int vf)
{
    for(int i=1;i<=n;i++)
    {
        parinte[i]=-1;
        drum[i]=inf;
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
bool BF(int n,int vf)
{

    init(n,vf);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j])
                relax(i,j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j])
    {
        if(drum[j]>drum[i]+a[i][j]&&drum[i]!=inf)
            return false;
    }
    return true;

}
int main()
{
    int n,m,in,sf;
    f>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        a[x][y]=z;
    }
    f>>in>>sf;
    BF(n,in);
    cout<<"Lungimea drumului: "<<drum[sf]<<"\n";
    while(sf!=-1)
    {
        cout<<sf<<" ";
        sf=parinte[sf];
    }
}
