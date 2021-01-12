#include <bits/stdc++.h>

using namespace std;

template<size_t N, size_t M, typename ...T>
struct getPosType;

template<size_t N, size_t M, typename TCur, typename ...T>
struct getPosType<N, M, TCur, T...>
{
    using type = typename getPosType<N, M+1, T...>::type;
};

template<size_t N, typename TCur, typename ...T>
struct getPosType<N, N, TCur, T...>
{
    using type = TCur;
};

template<size_t N, typename ...T>
using PosType = typename getPosType<sizeof...(T), sizeof...(T)-N, T...>::type;

template<size_t Index>
struct hash_impl{
    //template<typename T1, typename...T>
    template<typename...T>
   // void operator()(size_t& seed, const tuple<T1, T...>& p) const
    void operator()(size_t& seed, const tuple<T...>& p) const
    {
        hash_impl<Index-1>{}(seed, p);
       // seed = seed ^ (hash<T1>{}(get<Index>(p)));
        seed = seed ^ (hash<PosType<Index, T...>>{}(get<Index>(p)));
    }
};
template<>
struct hash_impl<0>{
    //template<typename T1, typename...T>
    template<typename...T>
   // void operator()(size_t& seed, const tuple<T1, T...>& p) const
    void operator()(size_t& seed, const tuple<T...>& p) const
    {
      //  seed = seed ^ (hash<T1>{}(get<0>(p)));
        seed = seed ^ (hash<PosType<0, T...>>{}(get<0>(p)));
    }
};

struct tuple_hash{
    template<typename...T>
    size_t operator()(const tuple<T...>& p) const
    {
        size_t seed = 0;
        hash_impl<sizeof...(T)>{}(seed, p);
        return seed;
    }
};

void makeCombs(size_t start, size_t left, size_t n, size_t mustHave, vector<size_t>& arr, vector<vector<size_t>>* res)
{
    if(left == 0) {
        res->push_back(arr);
        return;
    }

    for(size_t i = start; i < n; ++i) {
        if(i == mustHave)
            continue;
        arr.push_back(i);
        makeCombs(i+1, left-1, n, mustHave, arr, res);
        arr.pop_back();
    }
}

void combSets(size_t k, size_t n, size_t start, vector<vector<size_t>>* res)
{
    vector<size_t> arr;
    arr.push_back(start);

    makeCombs(0, k-1, n, start, arr, res);
}

struct set_hash{
    size_t operator()(const pair<vector<size_t>, size_t>& v) const
    {
        size_t seed = v.second;
        for(const auto& i : v.first)
            seed = seed^(hash<size_t>{}(i));
        return seed;
    }
};
double travelingSales(const vector<vector<double>>& w, size_t start)
{
    unordered_map<pair<vector<size_t>, size_t>, double, set_hash> cost;
    cost.emplace(make_pair(vector<size_t>{start}, start), 0);
    const size_t n = w.size();
    unordered_map<pair<vector<size_t>, size_t>, pair<vector<size_t>, size_t>, set_hash> prev;
    for(size_t s = 2; s <= n; ++s) {
        vector<vector<size_t>> sets;
        combSets(s, n, start, &sets);
        for(auto& v : sets)
            sort(v.begin(), v.end());
        for(const auto& si : sets) {
            cost.emplace(make_pair(si, start), numeric_limits<double>::max());
            for(const auto& j : si) {
                if(j == start) continue;
                double min = numeric_limits<double>::max();
                size_t minIdx = numeric_limits<size_t>::max();
                auto key = si;
                key.erase(find(key.begin(), key.end(), j));
                for(const auto& i : si) {
                    if(i == j) continue;
                    const double dist = cost.at(make_pair(key, i)) + w[i][j];
                    if(dist < min) {
                        min = dist;
                        minIdx = i;
                    }
                }
                cost.emplace(make_pair(si, j), min);
                prev.emplace(make_pair(si, j), make_pair(key, minIdx));
            }
        }
    }

    vector<size_t> full(n);
    iota(full.begin(), full.end(), 0);

    double min = numeric_limits<double>::max();
    size_t minIdx = numeric_limits<size_t>::max();
    for(size_t j = 0; j < n; ++j) {
        if(j == start) continue;
        double dist = cost.at(make_pair(full, j)) + w[j][start];
        if(dist < min) {
            min = dist;
            minIdx = j;
        }
    }

    cout << "route: ";
    auto pair = make_pair(full, minIdx);
    while(prev.count(pair) != 0) {
        cout << pair.second << "<-";
        pair = prev[pair];
    }
    cout << start << endl;
    return min;
}

int main()
{
    const size_t n = 5;
    vector<vector<double>> w(n,
                vector<double>(n, numeric_limits<double>::max()));
    w[0][1] = 2;
    w[0][2] = 2;
    w[0][3] = 1;
    w[0][4] = 4;
    w[1][0] = 2;
    w[1][2] = 3;
    w[1][3] = 2;
    w[1][4] = 3;
    w[2][0] = 2;
    w[2][1] = 3;
    w[2][3] = 2;
    w[2][4] = 2;
    w[3][0] = 1;
    w[3][1] = 2;
    w[3][2] = 2;
    w[3][4] = 4;
    w[4][0] = 4;
    w[4][1] = 3;
    w[4][2] = 2;
    w[4][3] = 4;

    cout << travelingSales(w, 2) << endl;
   // unordered_map<tuple<size_t, size_t, size_t>, double, tuple_hash> S;
   // vector<vector<size_t>> combs;
   // combSets(3, 5, 0, &combs);
   // for(const auto& i : combs) {
   //     for(const auto& j : i)
   //         cout << j << " ";
   //     cout << endl;
   // }
}
