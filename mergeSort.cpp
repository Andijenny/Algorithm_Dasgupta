#include <bits/stdc++.h>

namespace MY_ALG
{
    using namespace std;
    template<typename ForwardIt, typename Container>
    void merge(ForwardIt ibeg1, ForwardIt iend1, ForwardIt ibeg2, ForwardIt iend2, Container& container)
    {
        if(ibeg1 == iend1) {
            copy(ibeg2, iend2, back_inserter(container));
            return;
        }
        if(ibeg2 == iend2) {
            copy(ibeg1, iend1, back_inserter(container));
            return;
        }

        if(*ibeg1 <= *ibeg2) {
            copy(ibeg1, next(ibeg1), back_inserter(container));
            ibeg1++;
            merge(ibeg1, iend1, ibeg2, iend2, container);
        }
        else {
            copy(ibeg2, next(ibeg2), back_inserter(container));
            ibeg2++;
            merge(ibeg1, iend1, ibeg2, iend2, container);
        }
    }

    template<typename ForwardIt>
    int mergeSort(ForwardIt ibeg, ForwardIt iend)
    {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        deque<vector<value_type>> qm;

        for(auto it = ibeg; it != iend; ++it) {
            vector<value_type> tmp;
            tmp.push_back(*it);
            qm.push_back(tmp);
        }

        while(qm.size() > 1) {
            auto& val1 = qm[0];
            auto& val2 = qm[1];
            vector<value_type> valMerge;
            merge(val1.begin(), val1.end(), val2.begin(), val2.end(), valMerge);
            qm.pop_front();
            qm.pop_front();
            qm.push_back(valMerge);
        }

        const auto& sortedVec = qm.front();
        copy(sortedVec.begin(), sortedVec.end(), ibeg);
    }
}

int main()
{
    std::vector<int> vec = {3, 4, 1, 9, 8, 5, 2};
    MY_ALG::mergeSort(vec.begin(), vec.end());
    std::cout << "sorted array: " << std::endl;
    for(auto i : vec)
        std::cout << i << "  ";
    std::cout << std::endl;
}
