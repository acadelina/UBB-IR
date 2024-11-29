#include <iostream>
#include<fstream>
using namespace std;
ifstream f("matrice.txt");

int n,m[100][100];
int bfs(int start,int a[100][100])
{
  int i,k,st,dr,x[100],v[100];

  st=dr=1;
  x[1]=start;
  v[start]=1;
  while(st<=dr)
  {
    k=x[st];
    for(i=1;i<=n;i++)
      if(v[i]==0 && a[k][i]==1)
      {
        v[i]=1;
        x[++dr]=i;
      }
    st++;
  }
  return dr;
}
void rf(int a[100][100],int n)
{
    for(int k = 1 ; k <= n ; ++k)
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= n ; ++j)
                    if(a[i][j]<a[i][k]+a[k][j])
                        a[i][j] = a[i][k]+a[k][j];



}
int main()
{
    f>>n;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        f>>m[i][j];
    cout<<"Nodurile izolate: ";
    for(int i=1;i<=n;i++)
    {
        int ok=1;
        for (int j=1;j<=n;j++)
            if (m[i][j]==1)
                ok=0;
       if(ok==1)
        cout<<i<<", ";
    }
    cout<<'\n';
    int ok=1;
    int v[100];
    for (int i=1;i<=n;i++)
    {   int nr=0;
        for(int j=1;j<=n;j++)
            if (m[i][j]==1)
                nr++;
        v[i]=nr;

    }
    for (int i=1;i<n;i++)
        if(v[i]!=v[i+1])
            ok=0;
    if (ok==1)
        cout<<"Graful este regular"<<'\n';
    else
        cout<<"Graful nu este regular"<<'\n';
    ok=bfs(1,m);
    if(ok==n)
        cout<<"Graful este conex"<<'\n';
    else cout<<"Graful nu este conex"<<'\n';

    int a[100][100];

    rf(m,n);
    for (int i=1;i<=n;i++)
        {for (int j=1;j<=n;j++)
            cout<<m[i][j]<<" ";
        cout<<"\n";
        }




}
