#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream f("mat.txt");
ofstream g("rez.txt");
const int INF = 1<<30;
const int NMAX = 1005;

int n, m;
vector<vector<pair<int, int>>> G(NMAX), newG(NMAX);

vector<int> BellmanFord(int source) {
    vector<int> dist(n, INF);
    dist[source] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (auto& p : G[u]) {
                int v = p.first;
                int w = p.second;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }


    for (int u = 0; u < n; ++u) {
        for (auto& p : G[u]) {
            int v = p.first;
            int w = p.second;
            if (dist[u] != INF && dist[u] + w < dist[v]) {

                return vector<int>();
            }
        }
    }

    return dist;
}

vector<int> Dijkstra(int source) {
    queue<int> q;
    vector<int> dist(n+1);
    q.push(source);

    for(int i = 1; i <= n; ++i) {
        if(i != source) {
            dist[i] = INF;
        }
        else {
            dist[i] = 0;
        }
    }

    while(!q.empty()) {
        int val = q.front();
        q.pop();
        for(auto p : G[val]) {
            if(dist[val] + p.second < dist[p.first]) {
                q.push(p.first);
                dist[p.first] = dist[val] + p.second;
            }
        }
    }

    return dist;
}

void Johnson(ostream& g) {


    for(int i = 1; i <= n; ++i) {
        pair<int, int> p = make_pair(i, 0);
        G[0].push_back(p);
    }

    //BellmanFord
    vector<int> dist = BellmanFord(0);
    if(dist.empty()) {
        g << -1;
        return;
    }

    //Reponderam
    for(int i = 1; i <= n; ++i) {
        for(auto p : G[i]) {
            pair<int,int> newP;
            newP = p;
            newP.second += (dist[i] - dist[newP.first]);
            newG[i].push_back(newP);
        }
    }

    //Afisam graful reponderat
    for(int i = 1; i <= n; ++i) {
        for(auto p : newG[i]) {
            g << i-1 << " " << p.first-1 << " " << p.second << '\n';
        }
    }

    //Facem Dijkstra pt toate nodurile
    for(int i = 1; i <= n; ++i) {
        dist = Dijkstra(i);
        for(int i = 1; i <= n; ++i) {
            if(dist[i] == INF) {
                g << "INF";
            }
            else {
                g << dist[i];
            }
            g << " ";
        }
        g << '\n';
    }
}

int main() {


    f >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int x, y, w;
        f >> x >> y >> w;
        x++, y++;
        pair<int, int> p = make_pair(y, w);
        G[x].push_back(p);
    }

    Johnson(g);

    f.close();
    g.close();

    return 0;
}
