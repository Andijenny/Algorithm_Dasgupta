#include <bits/stdc++.h>

using namespace std;

struct pair_hash{
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        return h1^h2;
    }
};

size_t chainMatrixMulRec(const vector<size_t>& m, size_t st, size_t ed, unordered_map<pair<size_t,size_t>, size_t, pair_hash>& cost, unordered_map<pair<size_t,size_t>, pair<size_t,size_t>, pair_hash>& prev)
{
    if(cost.count(make_pair(st, ed)) != 0)
        return cost[make_pair(st, ed)];

    size_t minCij = numeric_limits<size_t>::max();
    size_t minIdx = numeric_limits<size_t>::max();
    for(size_t k = st; k < ed; ++k) {
        const size_t cikj = chainMatrixMulRec(m, st, k, cost, prev) + chainMatrixMulRec(m, k+1, ed, cost, prev) + m[st-1]*m[k]*m[ed];
        if(cikj < minCij) {
            minCij = cikj;
            minIdx = k;
        }
        cost[make_pair(st, ed)] = minCij;
        prev[make_pair(st, ed)] = make_pair(minIdx, m[st-1]*m[minIdx]*m[ed]);
    }
    return cost[make_pair(st, ed)];
}

size_t chainMatrixMul2(const vector<size_t>& m)
{
    const size_t n = m.size();
    unordered_map<pair<size_t,size_t>, size_t, pair_hash> cost;
    unordered_map<pair<size_t,size_t>, pair<size_t,size_t>, pair_hash> prev;
    for(size_t i = 1; i < n; ++i)
        cost[make_pair(i, i)] = 0;

    size_t ct = chainMatrixMulRec(m, 1, n-1, cost, prev);

    queue<pair<size_t,size_t>> qu;
    qu.push(make_pair(1, n-1));
    while(!qu.empty()) {
        auto p = qu.front();
        qu.pop();
        if(prev.count(p) != 0) {
            size_t k = prev[p].first;
            cout << "split " << p.first << " " << p.second << ": " << k << "-" << prev[p].second << endl;;
            if(k > p.first)
                qu.push(make_pair(p.first, k));
            if(k < p.second)
                qu.push(make_pair(k+1, p.second));
        }
    }
    cout << endl;
    return ct;
}

size_t chainMatrixMul(const vector<size_t>& m)
{
    const size_t n = m.size();
    vector<vector<size_t>> cost(n);
    for(size_t i = 1; i < n; ++i) {
        cost[i].resize(n);
        cost[i][i] = 0;
    }

    unordered_map<pair<size_t,size_t>, pair<size_t,size_t>, pair_hash> prev;
    for(size_t s = 1; s < n; ++s) {
        for(size_t i = 1; i < n-s; ++i) {
            size_t j = i + s;
            size_t minCij = numeric_limits<size_t>::max();
            size_t minIdx = numeric_limits<size_t>::max();
            for(size_t k = i; k < j; ++k) {
                const size_t cikj = cost[i][k] + cost[k+1][j] + m[i-1]*m[k]*m[j];
                if(cikj < minCij) {
                    minCij = cikj;
                    minIdx = k;
                }
            }
            cost[i][j] = minCij;
            prev[make_pair(i, j)] = make_pair(minIdx, m[i-1]*m[minIdx]*m[j]);
        }
    }

    queue<pair<size_t,size_t>> qu;
    qu.push(make_pair(1, n-1));
    while(!qu.empty()) {
        auto p = qu.front();
        qu.pop();
        if(prev.count(p) != 0) {
            size_t k = prev[p].first;
            cout << "split " << p.first << " " << p.second << ": " << k << "-" << prev[p].second << endl;;
            if(k > p.first)
                qu.push(make_pair(p.first, k));
            if(k < p.second)
                qu.push(make_pair(k+1, p.second));
        }
    }
    cout << endl;
    return cost[1][n-1];
}

int main()
{
  //  vector<size_t> m({50,20,1,10,100}); // A1: 50*20; A2: 20*1; A3:1*10;  A4:10*100
    //(a1*a2) * (a3*a4)
    vector<size_t> m({50,20,1,10,100,20,120,40,90}); // A1: 50*20; A2: 20*1; A3:1*10;  A4:10*100
    //(a1*a2)*((a3*a4)*a5*a6*a7*a8)
    cout << "vector implementation: " << chainMatrixMul(m) << endl;
    cout << "hash_map implementation: " << chainMatrixMul2(m) << endl;
}
