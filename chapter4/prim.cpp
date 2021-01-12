#include <bits/stdc++.h>

using namespace std;

namespace ns_prim{
using Graph = vector<vector<size_t>>;

struct pair_hash{
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        return (h1^h2);
    }
};

struct equal{
    template<typename T1, typename T2>
    bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2) const
    {
        return ((p1.first == p2.second) || (p1.first == p2.first)) && ((p1.second == p2.first) || (p1.second == p2.second));
    }
};

using Dist = std::unordered_map<std::pair<size_t, size_t>, int, pair_hash, equal>;

void prim(const Graph& g, const Dist& w)
{

    vector<int> dist(g.size(), numeric_limits<int>::max());
    dist[0] = 0;
    vector<size_t> prev(g.size(), 0);
    prev[0] = numeric_limits<size_t>::max();

    auto cmp = [&dist](size_t p1, size_t p2) {
        return dist[p1] < dist[p2];
    };

    priority_queue<size_t, vector<size_t>, decltype(cmp)> pq(cmp);
    pq.push(0);

    vector<bool> visited(g.size(), false);

    while(!pq.empty()) {
        size_t u = pq.top();
        pq.pop();

        if(visited[u]) continue;

        visited[u] = true;

        for(const auto& v : g[u]) {
            if(!visited[v] && dist[v] > w.at(make_pair(u, v))) {
                dist[v] = w.at(make_pair(u, v));
                pq.push(v);
                prev[v] = u;
            }
        }
    }

    for(size_t i = 1; i < prev.size(); ++i)
        cout << prev[i] << "--" << i << endl;
}
}

int main()
{
    using namespace ns_prim;
    const size_t n = 9;
    Graph g(n);
    g[0].insert(g[0].end(), {1,7});
    g[1].insert(g[1].end(), {0,2,7});
    g[2].insert(g[2].end(), {1,3,8});
    g[3].insert(g[3].end(), {2,4,5});
    g[4].insert(g[4].end(), {3,5});
    g[5].insert(g[5].end(), {2,3,4,6});
    g[6].insert(g[6].end(), {5,7,8});
    g[7].insert(g[7].end(), {0,1,6,8});
    g[8].insert(g[8].end(), {2,6,7});

    Dist w;
    w.emplace(make_pair(0,1), 4);
    w.emplace(make_pair(0,7), 8);
    w.emplace(make_pair(1,7), 11);
    w.emplace(make_pair(1,2), 8);
    w.emplace(make_pair(7,8), 7);
    w.emplace(make_pair(2,8), 2);
    w.emplace(make_pair(6,7), 1);
    w.emplace(make_pair(6,8), 6);
    w.emplace(make_pair(2,3), 7);
    w.emplace(make_pair(2,5), 4);
    w.emplace(make_pair(5,6), 2);
    w.emplace(make_pair(3,5), 14);
    w.emplace(make_pair(3,4), 9);
    w.emplace(make_pair(4,5), 10);
    w.emplace(make_pair(7,8), 1);

    prim(g, w);
}
