#include <iostream>
#include<fstream>
#define inf 10000
using namespace std;
ifstream f("mat.txt");
int a[100][100];
//Rpy Floyd costul drumului minim
void RF(int n)
{
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                if(a[i][j]>a[i][k]+a[k][j])
                    a[i][j]=a[i][k]+a[k][j];
        }
    }
}
//Roy Warshall matricea drumurilor/inchidere tranz
void RW(int n)
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j&&a[i][j]==0)
                    a[i][j]=a[i][k]*a[k][j];
}
int main()
{
    int n,m;
    f>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]=inf;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        a[x][y]=z;
    }
    RW(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
    {
        if(a[i][j]!=inf)
            cout<<i<<"->"<<j<<": "<<a[i][j]<<"\n";
        else
            cout<<i<<"->"<<j<<": "<<"INF"<<"\n";
    }
}
