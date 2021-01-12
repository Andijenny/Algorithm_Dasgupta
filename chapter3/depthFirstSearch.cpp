#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<size_t>>;

class dfs{
public:
    dfs(const vector<vector<size_t>>& g)
            : g_(g)
            , iter_(0)
            , clock_(0)
            , visited_(g.size(), false)
            , preVisit_(g.size(), 0)
            , postVisit_(g.size(), 0)
            , tree_(g.size())
    {
    }

    void search(size_t node, bool printOut = true)
    {
        if(visited_[node]) return;
        if(iter_ != 0 && printOut)
            cout <<  endl;
        search_(node, 0, node, printOut);
        iter_++;// strong connectivity number
    }

    //print strongly connected components
    void printScc()
    {
        cout << "Following are strongly connected components in given graph: \n";
        Graph gr = inverseGraph_(g_);

        dfs idfs_(gr);
        for(size_t i = 0; i < gr.size(); ++i)
            idfs_.search(i, false);

        dfs dfs_(g_);
        while(!idfs_.postStack_.empty()) {
            size_t n = idfs_.postStack_.top();
            idfs_.postStack_.pop();
            dfs_.search(n);
        }
    }

    void printClock() const
    {
        for(size_t i = 0; i < g_.size(); ++i) {
            cout << "node " << alphabeta_[i] << ": " << preVisit_[i] << "," << postVisit_[i]  << endl;
        }
    }

    void printEdgeType() const
    {
        vector<pair<size_t, size_t>> forward, back, cross;
        forward.reserve(g_.size());
        back.reserve(g_.size());
        cross.reserve(g_.size());

        for(size_t i = 0; i < g_.size(); ++i) {
            for(const auto& j : g_[i]) {
                if(preVisit_[i] < preVisit_[j]) {
                    if(postVisit_[i] > postVisit_[j]) { // i contains j
                        if(!tree_[i].empty() && find(tree_[i].begin(), tree_[i].end(), j) == tree_[i].end()) // not tree edge
                            forward.emplace_back(i, j);
                    }
                }
                else {
                    if(postVisit_[i] < postVisit_[j])
                        back.emplace_back(i, j);
                    else
                        cross.emplace_back(i, j);
                }
            }
        }

        cout << "forward: ";
        for(const auto&[i, j] : forward)
            cout << alphabeta_[i] << "-->" << alphabeta_[j] << ", ";
        cout << "\nback: ";
        for(const auto&[i, j] : back)
            cout << alphabeta_[i] << "-->" << alphabeta_[j] << ", ";
        cout << "\ncross: ";
        for(const auto&[i, j] : cross)
            cout << alphabeta_[i] << "-->" << alphabeta_[j] << ", ";
        cout << endl;

    }
private:
    void search_(size_t node, size_t step, size_t father, bool printOut)
    {
        if(printOut)
            cout<< placeholder_(step)  << alphabeta_[node] << endl;
        preVisit_[node] = clock_;
        clock_++;

        visited_[node] = true;
        if(father != node)
            tree_[father].push_back(node);
        for(size_t i = 0; i < g_[node].size(); ++i) {
            if(!visited_[g_[node][i]]) {
                search_(g_[node][i], step + 4, node, printOut);
            }
        }

        postVisit_[node] = clock_;
        postStack_.push(node);
        clock_++;
    }

    Graph inverseGraph_(const Graph& g) const
    {
        Graph ig(g.size());
        for(size_t i = 0; i < g.size(); ++i) {
            for(const auto& j : g[i]) {
                ig[j].push_back(i);
            }
        }
        return ig;
    }


    string placeholder_(size_t step)
    {
        if(step == 0) return "";

        string str = string(step-3, ' ');
        str.append(string(3, '-'));
        return str;
    }

    const char* alphabeta_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const Graph&    g_;
    size_t          clock_;
    size_t          iter_;
    vector<bool>    visited_;
    vector<size_t>  preVisit_;
    vector<size_t>  postVisit_;
    Graph           tree_;
public:
    stack<size_t>   postStack_;
};

int main()
{
//    vector<vector<size_t>> G(9);
//    G[0].insert(G[0].end(), {1, 4});
//    G[1].insert(G[1].end(), {1, 2, 4});
//    G[2].insert(G[2].end(), {1, 5});
//    G[3].insert(G[3].end(), {6, 7});
//    G[4].insert(G[4].end(), {1, 5});
//    G[5].insert(G[5].end(), {4, 8});
//    G[6].insert(G[6].end(), {3, 7});
//    G[7].insert(G[7].end(), {3, 6});
//    G[8].insert(G[8].end(), {5});
    // fig. 3.7
  //  const size_t n = 8;
  //  vector<vector<size_t>> G(n);
  //  G[0].insert(G[0].end(), {1, 2, 5});
  //  G[1].insert(G[1].end(), {4});
  //  G[2].insert(G[2].end(), {3});
  //  G[3].insert(G[3].end(), {0, 7});
  //  G[4].insert(G[4].end(), {5, 6, 7});
  //  G[5].insert(G[5].end(), {1, 6});
  //  G[7].insert(G[7].end(), {6});

    //fig. 3.9
    const size_t n = 12;
    vector<vector<size_t>> G(n);
    G[0].insert(G[0].end(), {1});
    G[1].insert(G[1].end(), {2, 3, 4});
    G[2].insert(G[2].end(), {5});
    G[4].insert(G[4].end(), {1, 5, 6});
    G[5].insert(G[5].end(), {2, 7});
    G[6].insert(G[6].end(), {7,9});
    G[7].insert(G[7].end(), {10});
    G[8].insert(G[8].end(), {6});
    G[9].insert(G[9].end(), {8});
    G[10].insert(G[10].end(), {11});
    G[11].insert(G[11].end(), {9});

    dfs dfs_(G);
    for(size_t i = 0; i < n; ++i) {
        dfs_.search(i);
    }
    dfs_.printClock();
    dfs_.printEdgeType();
    dfs_.printScc();
}
