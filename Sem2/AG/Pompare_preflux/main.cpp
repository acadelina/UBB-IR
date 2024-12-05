#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// muchie
class Edge{
public:
    int flow; // flow
    int cp; // capacitate
    int src; // sursa
    int dest; // destinatie

    // constructor
    Edge(int f,int c,int s, int d){
        flow = f;
        cp = c;
        src = s;
        dest = d;
    }
};

// nod
class Vertex
{
public:
    int h; // inaltime
    int e_flow; // exces flux

    // constructor
    Vertex(int inaltime, int exces){
        h = inaltime;
        e_flow = exces;
    }
};


// graf
class Graph
{
private:
    int nr_vf; // numar varfuri
    int nr_muchii; // numar muchii
    vector<Vertex> varfuri;
    vector<Edge> muchii;

public:
    // constructor
    Graph(int vf,int m)
    {
        nr_vf = vf;
        nr_muchii = m;
    }

    // adauga o muchie in graf
    void addEdge(int u,int v,int w){
        muchii.emplace_back(0,w,u,v);
    }

    // pomparea excesului de flux din u
    bool pompare(int u);

    // inaltarea unui varf
    void inaltare(int u);

    // initializarea prefluxului
    void initializare_preflux(int s);

    // fluxul maxim de la s la t
    int pompare_preflux(int s,int t);

    // actualizeaza fluxul muchiei inverse
    void actualizareMuchieInversa(int i,int flow);

    // returneaza indexul unui nod care are excesul > 0
    int overflow_vertex(vector<Vertex>& v);
};

void Graph::initializare_preflux(int s) {
    // initializarea varfurilor cu h=0 si e=0
    for(int i=0;i<nr_vf;i++)
        varfuri.emplace_back(Vertex(0,0));

    // fluxul muchiilor a fost initializat cu 0 in constr grf

    varfuri[s].h = nr_vf;

    for(int i=0;i<muchii.size();i++)
    {
        if(muchii[i].src == s)
        {
            // flow = capacitate
            muchii[i].flow = muchii[i].cp;

            // excesul de flux pentru vf adiacent
            varfuri[muchii[i].dest].e_flow += muchii[i].flow;

            // adaugarea unei muchii in graful rezidual cu cp = 0
            muchii.emplace_back(-muchii[i].flow,0,muchii[i].dest,s);
        }
    }
}

void Graph::actualizareMuchieInversa(int i, int flow) {
    int u = muchii[i].dest, v = muchii[i].src;

    for(int j=0;j<muchii.size();j++)
    {
        if(muchii[j].dest == v && muchii[j].src == u)
        {
            muchii[j].flow -= flow;
            return;
        }
    }

    // adaugarea muchiei inverse in graful rezidual
    Edge e = Edge(0,flow,u,v);
    muchii.push_back(e);
}

bool Graph::pompare(int u) {
    // traversarea tuturor muchiilor pentru a gasi vf adiacente ale lui u
    // catre care fluxul poate fi pompat
    for(int i=0;i<muchii.size();i++)
    {
        if(muchii[i].src == u)
        {
            // nu se mai poate pompa
            if(muchii[i].flow == muchii[i].cp)
                continue;

            if(varfuri[u].h > varfuri[muchii[i].dest].h)
            {
                int cant_flux = min(muchii[i].cp-muchii[i].flow,varfuri[u].e_flow);

                // reducerea excesului de flux
                varfuri[u].e_flow -= cant_flux;

                // adaugarea fluxului rezidual
                varfuri[muchii[i].dest].e_flow += cant_flux;

                // adagare flux rezidual
                muchii[i].flow += cant_flux;

                actualizareMuchieInversa(i,cant_flux);

                return true;
            }
        }
    }
    return false;

}

void Graph::inaltare(int u) {
    int min_h = INT_MAX;

    // varful adiacent cu h minim
    for(int i=0;i<muchii.size();i++)
    {
        if(muchii[i].src == u)
        {
            // flow = cp => nu e nevoie de inaltare
            if(muchii[i].flow == muchii[i].cp)
                continue;

            // actualizare min_h
            if(varfuri[muchii[i].dest].h < min_h)
            {
                min_h = varfuri[muchii[i].dest].h;

                varfuri[u].h = min_h + 1;
            }
        }
    }
}

int Graph::overflow_vertex(vector<Vertex> &v) {
    for(int i=1;i<varfuri.size()-1;i++)
    {
        if(varfuri[i].e_flow > 0)
            return i;
    }
    return -1; // nu exista un astfel de varf
}

int Graph::pompare_preflux(int s, int t) {
    initializare_preflux(s);

    while(overflow_vertex(varfuri) != -1)
    {
        int u = overflow_vertex(varfuri);
        if(!pompare(u))
            inaltare(u);
    }

    // varfuri.back() returneaza ultimul varf
    // al carui e_flow final va fi cel maxim
    return varfuri.back().e_flow;
}

int main() {
    ifstream f("2-in.txt");
    int vf,m;
    f>>vf>>m;
    Graph g(vf,m);


    int src,dest,w;
    for(int i=1;i<=m;i++)
    {
        f>>src>>dest>>w;
        g.addEdge(src,dest,w);
    }


    int s=0, t=vf-1;

    cout<<"Valoarea fluxului maxim este: "<<g.pompare_preflux(s,t);

    return 0;
}
