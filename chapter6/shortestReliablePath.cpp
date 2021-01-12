#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<size_t>>;
using Dist = vector<vector<double>>;

double shorestReliablePath(const Graph& g, const Dist& w, Dist& dist, vector<size_t>& prev, size_t st, size_t u, size_t k)
{
    if(k == 0 || abs(dist[u][k] - numeric_limits<double>::max()) > numeric_limits<double>::epsilon()){
        return dist[u][k];
    }

    for(const auto& v : g[u]) {
        double vi = shorestReliablePath(g, w, dist, prev, st, v, k-1);
        if(dist[u][k] > vi + w[v][u]) {
            dist[u][k] = vi + w[v][u];
            prev[u] = v;
        }
    }
    return dist[u][k];
}

int main()
{
    Graph g(6);
    g[0].insert(g[0].end(), {1,3,4});
    g[1].insert(g[1].end(), {0,2,4});
    g[2].insert(g[2].end(), {1,4,5});
    g[3].insert(g[3].end(), {0,4});
    g[4].insert(g[4].end(), {0,1,2,3,5});
    g[5].insert(g[5].end(), {2,4});

    const size_t k = 4;
    size_t u = 0;
    Dist w(6);
    Dist dist(6);
    for(size_t i = 0; i < 6; ++i) {
        w[i].resize(6);
        dist[i].resize(k+1);
        if(i == u)
            dist[i][0] = 0;
        else
            for(size_t j = 0; j <= k; ++j) {
                dist[i][j] = numeric_limits<double>::max();
            }
    }

    w[0][1] = 1;
    w[0][3] = 2;
    w[0][4] = 5;
    w[1][0] = 1;
    w[1][2] = 2;
    w[1][4] = 5;
    w[2][1] = 2;
    w[2][4] = 1;
    w[2][5] = 4;
    w[3][0] = 2;
    w[3][4] = 3;
    w[4][0] = 5;
    w[4][1] = 5;
    w[4][2] = 1;
    w[4][3] = 3;
    w[4][5] = 1;
    w[5][2] = 4;
    w[5][4] = 1;

    vector<size_t> prev(g.size(), g.size());
    cout << shorestReliablePath(g, w, dist, prev, u, 5, k) << endl;

    size_t i = 5;
    while(i != g.size()) {
        cout << i << " ";
        i = prev[i];
    }
    cout << endl;
}
