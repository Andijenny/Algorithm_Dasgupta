#include <bits/stdc++.h>

using namespace std;
using Graph = vector<vector<size_t>>;

struct pair_hash{
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        return (h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2)));
    }
};

using Dist = unordered_map<pair<size_t, size_t>, int, pair_hash>;

void dij(const Graph& g, size_t source, const Dist& w)
{
    const static int INFTY = numeric_limits<int>::max();
    vector<size_t> prev(g.size(), source);
    prev[source] = numeric_limits<size_t>::max();

    vector<int> dist(g.size());
    for(size_t i = 1; i < dist.size(); ++i) {
        if(i != source)
            dist[i]  = INFTY;
        else
            dist[i] = 0;
    }

    auto cmp = [&dist](size_t i, size_t j) ->bool {return dist[i] < dist[j];};
    priority_queue<size_t, vector<size_t>, decltype(cmp)> pq(cmp);

    pq.push(source);
    while(!pq.empty()) {
        size_t u = pq.top();
        pq.pop();
        for(const auto& v : g[u]) {
            if(dist[u] + w.at(make_pair(u, v)) < dist[v]) {
                dist[v] = dist[u] + w.at(make_pair(u, v));
                pq.push(v);
                prev[v] = u;
            }
        }
    }

    stack<pair<size_t, size_t>> st;
    st.emplace(source, 0);

    while(!st.empty()) {
        auto[u,step] = st.top();
        if(step > 0)
            cout << string(step-3, ' ') << string(3, '-');
        cout << u  << endl;
        st.pop();
        for(size_t i = 1; i < prev.size(); ++i) {
            if(prev[i] == u) {
                st.emplace(i, step+4);
            }
        }
    }
}

int main()
{
    const size_t n = 9;
    Graph g(n);
    g[1].insert(g[1].end(), {2,5,6});
    g[2].insert(g[2].end(), {3,6,7});
    g[3].insert(g[3].end(), {4,7});
    g[4].insert(g[4].end(), {7,8});
    g[5].insert(g[5].end(), {6});
    g[7].insert(g[7].end(), {6,8});

    Dist w;
    w.emplace(make_pair(1,2), 1);
    w.emplace(make_pair(1,5), 4);
    w.emplace(make_pair(1,6), 8);
    w.emplace(make_pair(2,3), 2);
    w.emplace(make_pair(2,6), 6);
    w.emplace(make_pair(2,7), 6);
    w.emplace(make_pair(3,4), 1);
    w.emplace(make_pair(3,7), 2);
    w.emplace(make_pair(4,8), 4);
    w.emplace(make_pair(4,7), 1);
    w.emplace(make_pair(5,6), 5);
    w.emplace(make_pair(7,6), 1);
    w.emplace(make_pair(7,8), 1);

    dij(g, 1, w);
}
