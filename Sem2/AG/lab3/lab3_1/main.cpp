#include <iostream>
#include <fstream>
#define inf 10000000
using namespace std;
ifstream f("1-in.txt");
ofstream g("1-out.txt");
int a[10005][10005], n, m, d[10005];

void Bellman(int nod){

    for(int i=0; i<n; i++)
        d[i]=inf;
    d[nod]=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            for(int k=0;k<n;k++)
                if(a[j][k])
                {if(d[k]>d[j]+a[j][k])
                   {
                       d[k]=d[j]+a[j][k];

                   }}
        }

    for(int i=0; i<n; i++)
            if(d[i]!=inf)
                g<<d[i]<<' ';
            else
                g<<"INF"<<" ";
    g<<endl;


}


int main(int argc, char* argv[])
{
    //ifstream f(argv[1]);
    //ofstream g(argv[2]);
    f>>n>>m;
    int nod;
    f>>nod;
    for(int j=0; j<m; j++){
        int x, y, c;
        f>>x>>y>>c;
        a[x][y]=c;
    }
    Bellman(nod);

    return 0;
}
