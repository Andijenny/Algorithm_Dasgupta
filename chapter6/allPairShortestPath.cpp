#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<size_t>>;
using Dist = vector<vector<double>>;

void allPairShortestPath(const Graph& g, const Dist& w, vector<vector<vector<double>>>& dist)
{
    for(size_t k = 1; k < g.size(); ++k) {
        size_t i = 0, j = 1;
        for(size_t i = 0; i < g.size(); ++i) {
            for(size_t j = 0; j < g.size(); ++j) {
                if(i == j) continue;
                dist[i][j][k] = min(dist[i][k][k-1] + dist[k][j][k-1], dist[i][j][k-1]);
            }
        }
    }

    for(size_t i = 0; i < g.size(); ++i) {
        for(size_t j = 0; j < g.size(); ++j) {
            if(j == i) continue;
            double min = numeric_limits<double>::max();
            size_t minIdx = numeric_limits<size_t>::max();
            for(size_t k = 0; k < g.size(); ++k)
                if(min > dist[i][j][k]) {
                    min = dist[i][j][k];
                    minIdx = k;
                }
            cout << "i " << i << ", j " << j << ", k " << minIdx << " : " << min << endl;
       //     cout << "i " << i << ", j " << j << " " << dist[i][j][k] << endl;
        }
    }
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

    Dist w(6);
    for(size_t i = 0; i < 6; ++i) {
        w[i].resize(6);
        for(size_t j = 0; j < 6; ++j) {
            w[i][j] = numeric_limits<double>::max();
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

    vector<vector<vector<double>>> dist(g.size());

    for(size_t i = 0;i < 6; ++i) {
        dist[i].resize(6);
        for(size_t j = 0; j < 6; ++j) {
            dist[i][j].resize(6);
            dist[i][j][0] = w[i][j];
            for(size_t k = 1; k < 6; ++k)
                dist[i][j][k] = numeric_limits<double>::max();
        }
//        dist[0][0][i] = 0;
    }

    allPairShortestPath(g, w, dist);
}
