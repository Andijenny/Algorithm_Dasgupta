#include <bits/stdc++.h>

using namespace std;

void knapsackRec(const vector<int>& v, const vector<int>& w, int wt, int wi, unordered_map<int, int>& k)
{
    if(k.count(wi) != 0) return k[wi];

    return knapsackRec(v, w, wi, k);
    
}
//with repetition
void knapsack(const vector<int>& v, const vector<int>& w)
{
    unordered_map<int, int> k; // weight, total values
    for(const auto& i : w) {
    }
}
