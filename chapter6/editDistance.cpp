#include <bits/stdc++.h>

using namespace std;

size_t editDistance(const string& str1, const string& str2)
{
    const size_t n1 = str1.size();
    const size_t n2 = str2.size();
    vector<vector<size_t>> e(n1);
    vector<vector<tuple<size_t, size_t, uint8_t>>> prev(n1);

    for(size_t i = 0; i < n1; ++i) {
        prev[i].resize(n2);
        e[i].resize(n2);
        e[i][0] = i;
        prev[i][0] = make_tuple(i==0?0:i-1, 0,0);
    }
    for(size_t j = 0; j < n2; ++j) {
        e[0][j] = j;
        prev[0][j] = make_tuple(0, j==0?0:j-1,1);
    }

    for(size_t i = 1; i < n1; ++i) {
        for(size_t j = 1; j < n2; ++j) {
            size_t min = e[i-1][j-1]+(str1[i]==str2[j] ? 0 : 1);
            auto anc = make_tuple(i-1, j-1, 2);//substitution or match
            if(min > e[i-1][j] + 1) {
                min = e[i-1][j] + 1;
                anc = make_tuple(i-1, j, 0); // delete
            }
            if(min > e[i][j-1]+1) {
                min = e[i][j-1] + 1;
                anc = make_tuple(i, j-1, 1); // insert
            }
            e[i][j] = min;
            prev[i][j] = anc;
        }
    }

    auto anc = prev[n1-1][n2-1];
    while (!(get<0>(anc) == 0) || !(get<1>(anc) == 0)) {
        switch(get<2>(anc)) {
            case 0:
                cout << "x ";break;
            case 1:
                cout << "i ";break;
            case 2:
                cout << "s/m ";break;
            default:
                break;
        }
        anc = prev[get<0>(anc)][get<1>(anc)];
    }
    cout << endl;
    return e[n1-1][n2-1];
}

int main()
{
    string str1("exponential");
    string str2("polynomial");

    cout << editDistance(str1, str2) << endl;
}
