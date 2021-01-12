#include <bits/stdc++.h>

using namespace std;

using Node = vector<size_t>;

size_t indSubsetsTree(const vector<Node>& tree, size_t r, vector<size_t>& num)
{
    if(num[r] != 0) return num[r]; // avoid replication

    if(tree[r].empty()) {
        num[r] = 1;
        return num[r];
    }


    size_t sum_children = 0;
    size_t sum_grandGhildren = 1;// include r itself
    for(const auto& c : tree[r]) {
        sum_children += indSubsetsTree(tree, c, num);
        for(const auto& gc : tree[c])
            sum_grandGhildren += indSubsetsTree(tree, gc, num);
    }
    num[r] = max(sum_children, sum_grandGhildren);
    return num[r];
}

int main()
{
    vector<Node> tree(18);
    tree[0].insert(tree[0].end(), {1,2,3,4,5});
    tree[1].insert(tree[1].end(), {6,7,8});
    tree[6].insert(tree[6].end(), {9,10,11});
    tree[8].insert(tree[8].end(), {12,13});
    tree[9].insert(tree[9].end(), {14,15});
    tree[11].insert(tree[11].end(), {16,17});

    vector<size_t> num(18, 0);
    cout << indSubsetsTree(tree, 0, num) << endl;
}
