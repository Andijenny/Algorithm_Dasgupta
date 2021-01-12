#include <bits/stdc++.h>

using namespace std;

#define MILES 200

double hotelPenality(const vector<double>& hotels)
{
    auto penality = [](double x){return (MILES - x)*(MILES - x);};

    vector<double> minp(hotels.size());
    vector<size_t> prev(hotels.size());
    minp[0] = 0;
    prev[0] = numeric_limits<size_t>::max();

    for(size_t i = 1; i < hotels.size(); ++i) {
        double min = numeric_limits<double>::max();
        size_t minIdx = numeric_limits<size_t>::max();
        for(int j = i - 1; j >= 0; --j) {
            if(hotels[j] - hotels[i] > MILES) break;
            double pi = minp[j] + penality(hotels[j] - hotels[i]);
            if(pi < min) {
                min = pi;
                minIdx = j;
            }
        }
        minp[i] = min;
        prev[i] = minIdx;
    }

    size_t cur = hotels.size() - 1;

    stack<double> st;

    while(prev[cur] != numeric_limits<size_t>::max()) {
        st.push(hotels[cur]);
        cur = prev[cur];
    }
    st.push(hotels[cur]);

    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return minp.back();
}

int main()
{
    vector<double> hotels({0, 80, 180, 210, 360});
    cout << hotelPenality(hotels) << endl;
}
