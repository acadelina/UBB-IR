#include <iostream>
#include<fstream>
using namespace std;
ifstream f("matrice.txt");

void bfs(int k,int vf[],int c[],int t[],int matr[][20],int n)
{
    int prim=1,ultim=1;
    c[prim]=k;
    t[k]=0;
    vf[k]=1;
    while (prim <= ultim)
	{
		if (c[prim] != k)
		{
			cout<<"Cel mai scurt drum de la "<< k<<" la "<< c[prim]<<" este: ";
			int nods = c[prim];
			while (nods != 0)
			{
				cout<<nods<<" ";
				nods = t[nods];
			}
			cout<<"\n";
		}

		for (int i = 1; i <= n; i++)
			if (matr[c[prim]][i] == 1 && vf[i] == 0)
			{
				vf[i] = 1;
				t[i] = c[prim];
				ultim++;
				c[ultim] = i;
			}
		prim++;
	}
}
int main()
{
    int n,m,m1[20][20],vf[20],c[20],x,y,varf,t[20];
    f>>n>>m;
    for(int i=1;i<=n;i++)
    {
        vf[i]=0;
        c[i]=0;
        t[i]=0;
        for(int j=1;j<=n;j++)
            m1[i][j]=0;
    }
    for(int i=1;i<=m;i++)
    {
        f>>x>>y;
        m1[x][y]=1;
    }
    cout<<"Varful pt algoritmul lui Moore: ";
    cin>>varf;
    bfs(varf,vf,c,t,m1,n);

}
