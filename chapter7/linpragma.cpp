#include "simplex.hpp"
#include <iostream>

int main()
{
    using namespace std;
    /*
     *Maximize   P   =   40x1   +   30x2
      Subject to:
            x1   +   2x2   ≤   16
            x1   +   x2   ≤   9
            3x1  +   2x2   ≤   24
            x1   ,   x2   ≥   0
     *
     * */
    vector<vector<double>> A;
    A.push_back(vector<double>({1, 2}));
    A.push_back(vector<double>({1, 1}));
    A.push_back(vector<double>({3, 2}));
    A.push_back(vector<double>({-1, 0}));
    A.push_back(vector<double>({0, -1}));
    vector<double> C({16, 9, 24, 0, 0});
    vector<double> F({40, 30});
    simplex slx(A, C, F);
    vector<double> optimx;
    double max = slx.solve(optimx);
    cout << "max value: " << max;
    cout << " at x = [ ";
    for(const auto& i : optimx)
        cout << i << " ";
    cout << "]" << endl;

    cout << "final A: \n" << slx.getFinalA() << endl; 
}
