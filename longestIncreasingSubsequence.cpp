#include <bits/stdc++.h>

using namespace std;
size_t longestIncreasingSubsequence(const vector<int>& arr)
{
    vector<int> length(arr.size(), 0);
    vector<size_t> prev(arr.size(), arr.size());
    for(size_t i = 0; i < arr.size(); ++i) {
        int max = length[i];
        for(size_t j = 0; j < i; ++j) {
            if(arr[j] < arr[i] && length[j] >= max) {
                max = length[j];
                prev[i] = j;
            }
        }
        length[i] = max + 1;
    }

    size_t maxIdx = 0;
    for(size_t i = 1; i < length.size(); ++i) {
        if(length[i] > length[maxIdx])
            maxIdx = i;
    }

    size_t i = maxIdx;
    while(true) {
        cout << arr[i] << "<-";
        i = prev[i];
        if(i == arr.size()) break;
    }
    cout << endl;
    return length[maxIdx];
}

int main()
{
    vector<int> arr({5,2,8,6,3,6,9,7});
    longestIncreasingSubsequence(arr);
}
