#include "simplex.hpp"
#include <iostream>

int main()
{
    using namespace std;

    vector<vector<double>> A;
    A.push_back(vector<double>({1, 1, 1, 1, 0, 0}));
    A.push_back(vector<double>({1, 1, 0, 0, 1, 1}));
    A.push_back(vector<double>({0,0,1,1,1,1}));
    A.push_back(vector<double>({1,0,0,1,0,1}));
    A.push_back(vector<double>({0,1,1,0,0,1}));
    A.push_back(vector<double>({0,1,0,1,1,0}));
    A.push_back(vector<double>({-1,-1,0,0,0,0}));
    A.push_back(vector<double>({0,0,-1,-1,0,0}));
    A.push_back(vector<double>({0,0,0,0,-1,-1}));
    vector<double> C({10,12,8,6,13,11,-2,-2,-2});
    vector<double> F({3,3,2,2,4,4});
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
