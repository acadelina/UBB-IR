#include <iostream>
#include <fstream>
#include <list>
#define MAX 50

using namespace std;

bool bfs(int graf_rez[][MAX],int s,int t,int parinte[],int nr_vf)
{
    bool visited[MAX]={false};

    list<int> q;

    visited[s] = true;
    q.push_back(s);

    parinte[s] = -1;

    while(!q.empty())
    {
        int curent = q.front();
        q.pop_front();

        for(int v=0;v<nr_vf;v++)
        {
            if(!visited[v] && graf_rez[curent][v] > 0)
            {
                // daca gasim o conexiune pana la t, nu mai este nevoie de BFS => e nevoie doar sa marcam parintele
                if(v==t)
                {
                    parinte[v] = curent;
                    return true;
                }

                visited[v] = true;
                parinte[v] = curent;
                q.push_back(v);
            }
        }
    }

    return false;
}


// fluxul maxim de la s -> t
int ford_fulkerson(int graf[][MAX],int s,int t,int nr_vf)
{
    // crearea unui graf rezidual, initial identic cu cel dat
    int graf_rez[MAX][MAX];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf_rez[i][j]=graf[i][j];

    // vector de parinti pentru BFS
    int parinte[nr_vf];
    int max_flow = 0;
    int u,v;

    while(bfs(graf_rez,s,t,parinte,nr_vf))
    {
        // caut capacitatea minima din drumul gasit prin BFS
        int path_flow = MAX;
        for(v=t;v!=s;v=parinte[v])
        {
            u=parinte[v];
            path_flow=min(path_flow,graf_rez[u][v]);
        }

        // actualizarea capacitatiilor reziduale
        //                 +
        // inversarea muchiilor din drumul gasit prin BFS
        for(v=t;v!=s;v=parinte[v])
        {
            u=parinte[v];
            graf_rez[u][v] -= path_flow;
            graf_rez[v][u] += path_flow;
        }

        // adaugare la fluxul maxim
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    ifstream f("2-in.txt");
    int nr_vf,nr_arce;
    f>>nr_vf>>nr_arce;

    int graf[MAX][MAX];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf[i][j]=0;

    int x,y,w;
    for(int i=1;i<=nr_arce;i++)
    {
        f>>x>>y>>w;
        graf[x][y]=w;
    }

    cout<<"Valoarea fluxului maxim este: "<<ford_fulkerson(graf,0,nr_vf-1,nr_vf);

    f.close();
    return 0;
}
