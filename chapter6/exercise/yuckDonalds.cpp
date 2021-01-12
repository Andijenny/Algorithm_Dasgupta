#include <bits/stdc++.h>

/*Yuckdonald’s is considering opening a series of restaurants along Quaint Valley Highway (QVH).
The n possible locations are along a straight line, and the distances of these locations from the
start of QVH are, in miles and in increasing order, m1, m2, . . . , mn. The constraints are as follows:
• At each location, Yuckdonald’s may open at most one restaurant. The expected proﬁt from

opening a restaurant at location i is pi, where pi > 0 and i = 1, 2, . . . , n.
• Any two restaurants should be at least k miles apart, where k is a positive integer.
Give an efﬁcient algorithm to compute the maximum expected total proﬁt subject to the given
constraints.
 * */

using namespace std;

double yuckdonald(const vector<double>& m, const vector<double>& p, double min_dis)
{
    const size_t n = m.size();
    vector<double> profit(n);
    profit[0] = 0;
    vector<size_t> prev(n);
    iota(prev.begin(), prev.end(), 0);

    for(size_t i = 1; i < n; ++i) {
        double maxp = 0;
        size_t k = i;
        for(size_t j = 0; j < i; ++j) {
            if(m[i]-m[j] >= min_dis) {
                if(maxp < profit[j] + p[i]) {
                    maxp = profit[j] + p[i];
                    k = j;
                }
            }
            else { // (a)
                if(maxp < profit[j]) {
                    maxp = profit[j];
                    k = j;
                }
            }
        }
        prev[i] = k;

        //There may or may not be a restaurant at location j. Those cases when there is no restaurant at location j will be considered by case l where l < j, so no additional operation is needed.
        profit[i] = maxp;
        if(maxp < p[i]) { // if this condition holds, then maxp must last come from (a) branch, that means now setting a store at i is better than one at k;
            profit[i] = p[i];
            prev[i] = i; // then store i will depend on it self, since for 0 to i-1, all the stores will have lower profits than sotre i
        }
      //  profit[i] = max(maxp, p[i]);
    }

    size_t cur = prev[n-1];
    while(prev[cur] != cur) {
        cout << m[cur] << " ";
        cur = prev[cur];
    }
    cout << m[cur] << endl;
    return profit.back();
}

int main()
{
    vector<double> m({1,4,9,11,18,20,23});
    vector<double> p({2,5,6,1,4,8,2});
    double min_dis = 10;
    cout << yuckdonald(m, p, min_dis) << endl;
}
