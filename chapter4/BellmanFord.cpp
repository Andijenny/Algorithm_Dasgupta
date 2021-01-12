#include <bits/stdc++.h>

using namespace std;
using Graph = vector<vector<size_t>>;

struct pair_hash{
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T1>{}(p.second);
        return (h1^h2);
    }
};
using Dist = unordered_map<pair<size_t, size_t>, double, pair_hash>;

void bell(const Graph& g, const Dist& w, size_t start)
{
    const auto max = numeric_limits<double>::infinity();
    vector<double> dist(g.size(), max);
    vector<size_t> prev(g.size(), 0);
    dist[start] = 0;
    prev[start] = numeric_limits<size_t>::max();

    for(size_t iter = 0; iter < g.size(); ++iter) {
        for(auto it = w.begin(); it != w.end(); ++it) {
            const size_t u = it->first.first;
            const size_t v = it->first.second;
            if(dist[v] > dist[u] + it->second) {
                dist[v] = dist[u] + it->second;
                prev[v] = u;
            }
        }
    }

    stack<pair<size_t, size_t>> st;
    st.push(make_pair(start, 0));

    while(!st.empty()) {
        auto[u, step] = st.top();
        st.pop();

        if(step > 0)
            cout << string(step-3, ' ') << string(3, '-');
        cout << u << endl;

        for(size_t i = 0; i < prev.size(); ++i) {
            if(prev[i] == u) {
                st.push(make_pair(i, step+4));
            }
        }
    }
}

int main()
{
    Graph g(10);
    g[0].insert(g[0].end(), {1, 3, 5, 6});
    g[1].insert(g[1].end(), {2, 3});
    g[2].insert(g[2].end(), {7, 8});
    g[3].insert(g[3].end(), {4, 6});
    g[5].insert(g[5].end(), {6, 8});
    g[6].insert(g[6].end(), {4});
    g[7].insert(g[7].end(), {9});
    g[8].insert(g[8].end(), {7});
    g[9].insert(g[9].end(), {8});
 
    Dist w;
    w.emplace(make_pair(1, 2), 4);
    w.emplace(make_pair(1, 3), -2);
    w.emplace(make_pair(2, 7), -2);
    w.emplace(make_pair(2, 8), -4);
    w.emplace(make_pair(3, 4), 2);
    w.emplace(make_pair(3, 6), 1);
    w.emplace(make_pair(5, 8), 3);
    w.emplace(make_pair(5, 6), -2);
    w.emplace(make_pair(6, 4), 3);
    w.emplace(make_pair(7, 9), -1);
    w.emplace(make_pair(8, 7), 1);
    w.emplace(make_pair(9, 8), 1);
    w.emplace(make_pair(0, 1), 7);
    w.emplace(make_pair(0, 2), 6);
    w.emplace(make_pair(0, 6), 5);

    bell(g, w, 0);
}
