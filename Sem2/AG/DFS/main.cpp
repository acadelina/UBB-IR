#include <iostream>
#include<fstream>
using namespace std;
ifstream f("mat.txt");

int m[100][100],vizitat[100];
void dfs(int inceput,int n)
{   int i;

    vizitat[inceput] = 1;
    for(i=1;i<=n;i++)
    {
        if(vizitat[i]==0 && m[inceput][i]==1)
            dfs(i,n);
    }

}
int main()
{
    int n,m1;
    f>>n>>m1;
    for(int i=1;i<=m1;i++)
    {
        int x,y;
        f>>x>>y;
        m[x][y]=1;
    }
    dfs(1,n);
    for(int i=1;i<=n;i++)
        if(vizitat[i])
            cout<<i<<" ";
}
