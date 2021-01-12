#include <bits/stdc++.h>

int kth_smallest(const std::vector<int>& arr, size_t k)
{
    if(arr.size() == 1) return arr[0];

    srand(time(0));
    size_t n = arr.size();
    auto pivot = arr[rand()%n];
    std::vector<int> vlt;
    std::vector<int> veq;
    std::vector<int> vgt;
    vlt.reserve(n);
    veq.reserve(n);
    vgt.reserve(n);
    size_t lt = 0, eq = 0;
    for(const auto& v : arr) {
        if(v < pivot) vlt.push_back(v);
        else if(v == pivot) veq.push_back(v);
        else vgt.push_back(v);
    }

    if(k <= vlt.size())
        return kth_smallest(vlt, k);
    if(k <= veq.size() + vlt.size())
        return pivot;
    return kth_smallest(vgt, k-veq.size()+vlt.size());
}

int main()
{
    std::cout << "input n: ";
    size_t n;
    std::cin >> n;
    std::vector<int> vec(n);
    srand(time(0));
    std::cout << "vec: ";
    for(size_t i = 0; i < n; ++i) {
        vec[i] = rand()%20;
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;
    size_t k;
    std::cout << "input k: ";
    std::cin >> k;
    std::cout << k << "th smallest: " << kth_smallest(vec, k) << std::endl;
}
