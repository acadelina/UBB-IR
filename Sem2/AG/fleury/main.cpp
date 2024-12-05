#include <iostream>
#include <fstream>
#define MAX_V 50
using namespace std;

// cauta nodul de start pentru algoritm
int cauta_nod_start(int graf_copy[][MAX_V], int nr_vf)
{
    for(int i=0;i<nr_vf;i++)
    {
        int grad = 0;
        for(int j=0;j<nr_vf;j++)
        {
            if(graf_copy[i][j]==1)
                grad++;
        }
        if(grad%2!=0)
            return i; // varf impar => se incepe de la el cautarea
    }
    return 0; // toate nodurile au grad par (teorema graf eulerian) => se poate incepe de la 0 cautarea
}

// numara cate muchii sunt in graf
int nr_muchii(int graf_copy[][MAX_V],int nr_vf)
{
    int cate=0;
    for(int i=0;i<nr_vf;i++)
    {
        for(int j=0;j<nr_vf;j++)
        {
            if(graf_copy[i][j]==1)
                cate++;
        }
    }
    return cate;
}

// verifica daca muchia (u,v) este punte
bool e_punte(int u,int v, int graf_copy[][MAX_V], int nr_vf)
{
    int grad = 0;
    for(int i=0;i< nr_vf;i++)
    {
        if(graf_copy[v][i])
        {
            grad++;
        }
        if(grad>1)
            return false;
    }
    return true;
}


void fleury(int start, int graf_copy[][MAX_V], int nr_vf)
{
    static int muchii = nr_muchii(graf_copy,nr_vf);
    for(int v=0;v<nr_vf;v++)
    {
        // daca muchia exista si nu este punte
        if(graf_copy[start][v]==1)
        {
            if(muchii<=1  || !e_punte(start,v,graf_copy,nr_vf))
            {
                cout<<start<<"--"<<v<<" ";
                // stergerea muchiei din graf
                graf_copy[start][v] = 0;
                graf_copy[v][start] = 0;

                // scaderea nr de muchii
                muchii--;

                fleury(v,graf_copy,nr_vf);
            }
        }
    }
}

int main() {
    ifstream f("2-in.txt");

    int nr_vf,nr_m;
    f>>nr_vf>>nr_m;

    int graf[MAX_V][MAX_V];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf[i][j]=0;


    int a,b;
    for(int i=1;i<=nr_m;i++)
    {
        f>>a>>b;
        graf[a][b]=1;
        graf[b][a]=1;
    }

    // copie graf
    int graf_copy[MAX_V][MAX_V];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf_copy[i][j]=graf[i][j];

    cout<<"Ciclu eulerian: ";
    fleury(cauta_nod_start(graf_copy,nr_vf),graf_copy,nr_vf);


    f.close();
    return 0;
}
