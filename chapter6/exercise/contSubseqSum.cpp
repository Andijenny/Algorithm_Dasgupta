#include <bits/stdc++.h>

using namespace std;

double contSubseqSum(const vector<double>& arr)
{
    if(arr.empty())
        return 0;
    vector<double> sum(arr.size());
    vector<size_t> prev(arr.size());
    sum[0] = arr[0];
    prev[0] = 0;
    for(size_t i = 1; i < arr.size(); ++i) {
        if(sum[i-1] <= 0) {
            sum[i] = arr[i];
            prev[i] = i;
        }
        else {
            sum[i] = sum[i-1]+arr[i];
            prev[i] = i-1;
        }
    }

    double maxSum = 0; // length 0
    size_t maxIdx = 0;
    for(size_t i = 0; i < sum.size(); ++i) {
        if(sum[i] > maxSum) {
            maxSum = sum[i];
            maxIdx = i;
        }
    }

    stack<double> st;
    size_t cur = maxIdx;
    while(cur != prev[cur]) {
        st.push(arr[cur]);
        cur = prev[cur];
    }
    st.push(arr[cur]);

    while(!st.empty()) {
        auto cur = st.top();
        st.pop();
        cout << cur << " ";
    }
    cout << endl;

    return maxSum;
}

int main()
{
    vector<double> arr({5, 15, -30, 10, -5, 40, 10});
    cout << contSubseqSum(arr) << endl;
}
