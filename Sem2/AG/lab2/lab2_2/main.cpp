#include <iostream>
#include<fstream>
using namespace std;
ifstream f("matrice.txt");
int a[100][100],b[100][100];


void inchidereTranz(int a[100][100],int fin[100][100],int n)
{
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
    {
        fin[i][j]=a[i][j];
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
    {
        if(fin[i][j]==0)
            fin[i][j]=(fin[i][k]&&fin[k][j]);
    }
}
int main()
{
    int n,i,j,x,y,m;
    f>>n>>m;
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        a[x][y]=1;
    }
    inchidereTranz(a,b,n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<b[i][j]<<" ";
        cout<<'\n';
    }
}
