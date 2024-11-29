#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#define inf 100000
using namespace std;
ifstream f("mat.txt");

int a[100][100],drum[100],parinte[100],rez[100];
void schimba()
{
    int n,m,a[100][100],in[100][100],la[100][100];
    f>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int x,y
        f>>x>>y;
        a[x][y]=a[y][x]=1;
        la[x][0]++;
        la[y][0]++;
        la[x][la[x][0]]=y;
        la[y][la[y][0]]=x;
        in[x][i]=1;
        in[y][i]=1;
    }
}
void RF(int n,int v)
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(a[i][j]>a[i][k]+a[k][j])
                a[i][j]=a[i][k]+a[k][j];

}
void RW(int n,int vf)
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j&&a[i][j]==0)
                a[i][j]=a[i][k]*a[k][j];
}
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
    if(drum[v]>drum[u]+a[u][v])
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
}
int main()
{
    int n,m,in,sf;
    f>>n>>m>>in>>sf;
    for(int i=0;i<m;i++)
    {
        int x,y;
        f>>x>>y;
        a[x][y]=1;
    }
    dfs(n,in);
    //drum_moore(n,sf);
    for(int i=0;i<n;i++)
        if(drum[i])
        cout<<i<<" ";
}
