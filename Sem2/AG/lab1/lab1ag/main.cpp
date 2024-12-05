#include <iostream>
#include<fstream>
using namespace std;
ifstream f("muchii.txt");

int n,m,ma[10][10],la[10][10],mi[10][10],x,y;
int main()
{

    f>>n>>m;
    for (int i=1;i<=m;i++)
    {
        f>>x>>y;
        ma[x][y]=ma[y][x]=1;
        mi[x][i]=mi[y][i]=1;
        la[x][0]++;
        la[y][0]++;
        la[x][la[x][0]]=y;
        la[y][la[y][0]]=x;

    }
    cout<<"Matricea de adiacenta:"<<'\n';
    for (int i=1;i<=n;i++)
       {
        for(int j=1;j<=n;j++)
            cout<<ma[i][j]<<" ";
        cout<<'\n';
       }
    cout<<"Matricea de incidenta:"<<'\n';
    for (int i=1;i<=n;i++)
       {
        for(int j=1;j<=m;j++)
            cout<<mi[i][j]<<" ";
        cout<<'\n';
       }
    cout<<"Lista de adiacenta:"<<'\n';
    for (int i=1;i<=n;i++)
       {cout<<i<<": ";
        for(int j=1;j<=la[i][0];j++)
            cout<<la[i][j]<<", ";
        cout<<'\n';
       }
}


