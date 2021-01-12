#include <bits/stdc++.h>

using namespace std;

struct Node {
    size_t par_ = 0;
    size_t rank_ = 0;
};

class unionFindSet {
public:
    void makeset(size_t size)
    {
        arr_.resize(size);
        for(size_t i = 0; i < size; ++i)
            arr_[i].par_ = i;
    }
    /* log(V)
    size_t find(size_t id)
    {
        while(id != arr_[id].par_)
            id = arr_[id].par_;
        return id;
    }
    */

    //path compression
    size_t find(size_t id)
    {
        if(id != arr_[id].par_)
            arr_[id].par_ = find(arr_[id].par_);
        return arr_[id].par_;
    }

    void union1(size_t i, size_t j)
    {
        auto ri = find(i);
        auto rj = find(j);

        if(ri == rj) return;

        if(arr_[ri].rank_ > arr_[rj].rank_)
            arr_[rj].par_ = ri;
        else {
            arr_[ri].par_ = rj;
            if(arr_[ri].rank_ == arr_[rj].rank_)
                arr_[rj].rank_++;
        }
    }

private:
    vector<Node>    arr_;
};

using Edge = vector<pair<size_t, size_t>>;

void kruskal(size_t v, const Edge& e, const vector<double>& w)
{
    vector<size_t> idx(e.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&w](size_t i, size_t j){return w[i] < w[j];});

    vector<pair<size_t, size_t>> sortedEdges;
    sortedEdges.reserve(e.size());
    for(const auto& i : idx)
        sortedEdges.push_back(e[i]);
    unionFindSet set;
    set.makeset(v);

    vector<pair<size_t,size_t>> mst;
    for(const auto& p : sortedEdges) {
        if(set.find(p.first) != set.find(p.second)) {
            mst.push_back(p);
            set.union1(p.first, p.second);
        }
    }
    for(const auto& i : mst)
        cout << i.first << "--" << i.second << endl;
}

int main()
{
    Edge edge;
    vector<double> w;
    edge.emplace_back(0, 1);
    w.push_back(2);
    edge.emplace_back(0, 2);
    w.push_back(1);
    edge.emplace_back(1, 2);
    w.push_back(2);
    edge.emplace_back(1, 3);
    w.push_back(1);
    edge.emplace_back(2, 3);
    w.push_back(2);
    edge.emplace_back(2, 4);
    w.push_back(3);
    edge.emplace_back(3, 4);
    w.push_back(3);
    edge.emplace_back(3, 5);
    w.push_back(4);
    edge.emplace_back(4, 5);
    w.push_back(1);

    kruskal(6, edge, w);
}

