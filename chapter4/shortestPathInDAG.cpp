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

void topoSort(const Graph& g, vector<size_t>& sortedList)
{
    vector<bool> visited(g.size(), false);
    vector<bool> post(g.size());

    size_t clock = 0;

    stack<size_t> st;
    for(size_t i = 0; i < g.size(); ++i) {
        st.push(i);

        while(!st.empty()) {
            size_t u = st.top();
            st.pop();
            if(visited[u]) continue;
            visited[u] = true;
            clock++;

            for(const auto& v : g[u]) {
                if(!visited[v])
                    st.push(v);
            }

            post[u] = clock;
            clock++;
        }
    }

    size_t start = 0;
    for(size_t i = 1; i < post.size(); ++i) {
        if(post[i] > post[start])
            start = i;
    }

    fill(visited.begin(), visited.end(), false);
    st.push(start);
    while(!st.empty()) {
        size_t u = st.top();
        st.pop();
        if(visited[u]) continue;

        visited[u] = true;
        sortedList.push_back(u);

        for(const auto& v : g[u]) {
            if(!visited[v])
                st.push(v);
        }
    }
}

template<bool negate = false>
void shortestPathInDAG(const Graph& g, const Dist& w, size_t start)
{
    auto max = numeric_limits<double>::infinity();
    vector<double> dist(g.size(), max);
    dist[start] = 0;

    vector<size_t> prev(g.size(), start);
    prev[start] = numeric_limits<size_t>::max();

    vector<size_t> sortedList;
    topoSort(g, sortedList);

    for(const auto& u : sortedList) {
        for(const auto& v : g[u]) {
            if(dist[v] > dist[u] + w.at(make_pair(u, v))) {
                dist[v] = dist[u] + w.at(make_pair(u, v));
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
    cout << "dist: ";
    for(const auto& i : dist)
        cout << i << ", ";
    cout << endl;
}

int main()
{
    Graph g(5);
    g[0].insert(g[0].end(), {1, 2});
    g[1].insert(g[1].end(), {2, 4});
    g[2].insert(g[2].end(), {3});
    g[3].insert(g[3].end(), {4});
 
    Dist w;
    w.emplace(make_pair(0, 1), 3);
    w.emplace(make_pair(0, 2), 2);
    w.emplace(make_pair(1, 2), 5);
    w.emplace(make_pair(1, 4), 1);
    w.emplace(make_pair(2, 3), -3);
    w.emplace(make_pair(3, 4), 4);

    shortestPathInDAG(g, w, 0);
}
