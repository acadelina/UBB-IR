#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;

ifstream f("labirint_1.txt");
int a[1000][1000];
int n=0,m,x1,y1,x2,y2;
char s[1000];

void bordare()
{

    for(int i=0;i<=n+1;i++)
        a[i][0]=a[i][m+1]=-1;
    for(int i=0;i<=m+1;i++)
        a[0][i]=a[n+1][i]=-1;
}

void lee(int x,int y)
{
    if(x==x2&&y==y2)
        return;
    if(a[x+1][y]==0||a[x][y]+1<a[x+1][y])
    {
        a[x+1][y]=a[x][y]+1;
        lee(x+1,y);
    }
    if(a[x-1][y]==0||a[x][y]+1<a[x-1][y])
    {
        a[x-1][y]=a[x][y]+1;
        lee(x-1,y);
    }
    if(a[x][y+1]==0||a[x][y]+1<a[x][y+1])
    {
        a[x][y+1]=a[x][y]+1;
        lee(x,y+1);
    }
    if(a[x][y-1]==0||a[x][y]+1<a[x][y-1])
    {
        a[x][y-1]=a[x][y]+1;
        lee(x,y-1);
    }
}
int main()
{
    while(f.getline(s,1005))
    {
        n++;
        m=strlen(s);
        for(int i=0;i<strlen(s);i++)
        {
            if(s[i]=='1')
                a[n][i+1]=-1;
            else if(s[i]==' ')
                a[n][i+1]=0;
            else if(s[i]=='S')
            {
                a[n][i+1]=1;
                x1=n;
                y1=i+1;
            }
            else
            {
                x2=n;
                y2=i+1;
            }
        }
    }
    bordare();
    lee(x1,y1);
    cout<<"Lungimea drumului: "<<a[x2][y2]<<"\n";
    int x,y;
    x=x2,y=y2;
    while(x!=x1||y!=y1)
    {
        if(a[x-1][y]+1==a[x][y])
        {
            a[x][y]=-2;
            x--;
        }
        else if(a[x+1][y]+1==a[x][y])
        {
            a[x][y]=-2;
            x++;
        }
        else if(a[x][y-1]+1==a[x][y])
        {
            a[x][y]=-2;
            y--;
        }
        else if(a[x][y+1]+1==a[x][y])
        {
            a[x][y]=-2;
            y++;
        }
    }
    a[x2][y2]=-3;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==-1)
                cout<<'1';
            else if(a[i][j]==1)
                cout<<'S';
            else if(a[i][j]==-2)
                cout<<'D';
            else if(a[i][j]==-3)
                cout<<'F';
            else
                cout<<' ';
        }

        cout<<'\n';
    }
}
