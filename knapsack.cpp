#include <bits/stdc++.h>

using namespace std;

int knapsackRec(const vector<int>& v, const vector<int>& w, int wt, unordered_map<int, int>& k, unordered_map<int, int>& prev)
{
    if(k.count(wt) != 0) return k[wt];

    size_t maxIdx = numeric_limits<size_t>::max();
    int maxk = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        if(w[i] <= wt) {
            int vt = knapsackRec(v, w, wt-w[i], k, prev);
            if(vt + v[i] > maxk) {
                maxk = vt + v[i];
                maxIdx = i;
                prev[wt] = wt-w[i];
            }
        }
    }
    k.emplace(wt, maxk);
    return maxk;
}
//with repetition
int knapsack(const vector<int>& v, const vector<int>& w, int Wt)
{
    unordered_map<int, int> k; // weight, total values
    k.emplace(0, 0);
    unordered_map<int, int> prev;

    int vt = knapsackRec(v, w, Wt, k, prev);
    int wi = Wt;
    while(prev.count(wi) != 0) {
        cout << wi-prev[wi] << ", ";
        wi = prev[wi];
    }
    cout << endl;
    return vt;
}


struct pair_hash {
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        return (h1^h2);
    }
};


int knapsackWithoutRepetitionRev(const vector<int>& v, const vector<int>& w, int Wt, size_t n, unordered_map<pair<int, size_t>, int, pair_hash>& k, unordered_map<int, int>& prev)
{
    if(k.count(make_pair(Wt, n)) != 0)
        return k[make_pair(Wt, n)];
    if(n == 0 || Wt == 0)
        return 0;

    if(w[n-1] > Wt) {
        k[make_pair(Wt, n)] = knapsackWithoutRepetitionRev(v, w, Wt, n-1, k, prev);
    }
    else {
        k[make_pair(Wt, n)] = knapsackWithoutRepetitionRev(v, w, Wt, n-1, k, prev);
        int vt = knapsackWithoutRepetitionRev(v, w, Wt-w[n-1], n-1, k, prev)+v[n-1];
        if(k[make_pair(Wt, n)] < vt) {
            k[make_pair(Wt, n)] = vt;
            prev[Wt] = Wt-w[n-1];
        }
    }
    return k[make_pair(Wt, n)];
}

// without repetition
int knapsackWithoutRepetition(const vector<int>& v, const vector<int>& w, int Wt)
{
    unordered_map<pair<int, size_t>, int, pair_hash> k;
  //  for(size_t i = 0; i < w.size(); ++i) {
  //      k.emplace(make_pair(0, i+1), 0);
  //  }
  //  for(int i = 0;i <= Wt; ++i) {
  //      k.emplace(make_pair(i, 0), 0);
  //  }
    unordered_map<int, int> prev;
    int vt = knapsackWithoutRepetitionRev(v, w, Wt, v.size(), k, prev);

    int wi = Wt;
    while(prev.count(wi) != 0) {
        cout << wi-prev[wi] << ", ";
        wi = prev[wi];
    }
    cout << endl;
    return vt;
}

int main()
{
    vector<int> v({30,14,16,9});
    vector<int> w({6,3,4,2});
    int Wt = 10;
    cout << "with repetition: ";
    cout << knapsack(v, w, Wt) << endl;
    cout << "without repetition: ";
    cout << knapsackWithoutRepetition(v, w, Wt) << endl;
}

