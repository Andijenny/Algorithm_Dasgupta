#include <bits/stdc++.h>

using namespace std;

const size_t NL = numeric_limits<size_t>::max();

struct Node{
    size_t left = NL;
    size_t right = NL;
    string code = "";
};

void huffman(const vector<double>& freq) 
{
    const size_t n = freq.size();
    vector<double> f(2*n-1);
    vector<Node> tree(2*n-1);

    copy(freq.begin(), freq.end(), f.begin());
    auto cmp = [&f](size_t i, size_t j) {return f[i] > f[j];};
    priority_queue<size_t, vector<size_t>, decltype(cmp)> pq(cmp);

    for(size_t i = 0; i < n; ++i) {
        pq.push(i);
    }

    for(size_t k = n; k < 2*n-1; ++k) {
        size_t i = pq.top();
        pq.pop();
        size_t j = pq.top();
        pq.pop();
        f[k] = f[i] + f[j];
        tree[k].left = i;
        tree[k].right = j;
        pq.push(k);
    }

    stack<pair<size_t, string>> st;
    st.push(make_pair(2*n-2, string("")));
    while(!st.empty()) {
        const auto[cur, code] = st.top();
        st.pop();
        tree[cur].code = code;
        size_t l = tree[cur].left;
        size_t r = tree[cur].right;
        if(l != NL && r != NL) {
            st.push(make_pair(l, code+"0"));
            st.push(make_pair(r, code+"1"));
        }
    }

    for(size_t i = 0; i < n; ++i)
        cout << freq[i] << ": " << tree[i].code << endl;
}

int main()
{
    vector<double> freq({70, 3, 20,37});
    huffman(freq);
}
