#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ifstream fin("in.txt");

struct Nod {
    int h = 0;
    int e = 0;
};

void citire(vector<vector<int>>& G, int& N, int& M) {
    fin >> N >> M;
    for (int i = 0;i < N;i++) {
        vector<int> linie(N);
        G.push_back(linie);
    }
    int x, y, z;
    for (int i = 0;i < M;i++) {
        fin >> x >> y >> z;
        G[x][y] = z;
    }
}

void pompare(int x, vector<vector<int>>& G, vector<Nod>& noduri, set<int>& activ) {
    for (int i = 0;i < G.size();i++) {
        if (G[x][i] != 0 && noduri[i].h == noduri[x].h - 1) {
            int f = min(noduri[x].e, G[x][i]);
            G[x][i] -= f;
            G[i][x] += f;
            noduri[x].e -=f;
            noduri[i].e += f;
            activ.insert(i);
        }
    }
}

void inaltare(int x, vector<vector<int>>& G, vector<Nod>& noduri) {
    int minim = INT_MAX;
    for (int i = 0;i < G.size();i++) {
        if (G[x][i] != 0) {
            minim = min(minim, noduri[i].h);
        }
        noduri[x].h = minim + 1;
    }
}

int pompare_topologica(int s, int d, vector<vector<int>> G) {
    vector<vector<int>> GRez = G;

    int inaltime = G.size();
    vector<Nod> noduri(inaltime);
    noduri[s].h = inaltime;
    set<int> activ;

    for (int i = 0; i < G[s].size(); i++) {
        if (G[s][i] != 0) {
            noduri[i].e = G[s][i];
            GRez[i][s] = G[s][i];
            GRez[s][i] = 0;
            activ.insert(i);
        }
    }

    while (!activ.empty()) {
        int x = *activ.begin();
        activ.erase(activ.begin());
        if (x != s && x != d) {
            while (noduri[x].e > 0) {
                pompare(x, GRez, noduri, activ);
                inaltare(x, GRez, noduri);
            }
        }
    }
    return noduri[d].e;
}

int main()
{
    vector<vector<int>> G;
    int N, M;
    citire(G, N, M);
    cout << pompare_topologica(0, G.size() - 1, G);
    return 0;
}
