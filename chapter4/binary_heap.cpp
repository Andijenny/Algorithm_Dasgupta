#include <vector>
#include <iostream>
#include <string>
#include <initializer_list>

template<typename T, typename cmpType = std::less<T>>
class binary_heap{
public:
    binary_heap()
        : cmp_(cmpType{})
    {
    }
    binary_heap(const cmpType& cmpObj)
        : cmp_(cmpObj)
    {
    }

    template<typename Val>
    void insert(const std::initializer_list<Val>& arr)
    {
        for(const auto& i : arr)
            insert(i);
    }

    void insert(const T& val)
    {
        if(size_ >= arr_.size())
            arr_.resize(2*size_);
        arr_[size_] = val;
        bubble_(size_);
        size_++;
    }

    T deleteMin()
    {
        if(size_ == 1)
            throw("empty queue");
        T root = arr_[1];

        size_--;
        arr_[1] = arr_[size_];
        sift_(1);
        return root;
    }

    void print() const
    {
        print_(1, 0);
    }

    bool empty() const
    {
        return size_ <= 1;
    }
private:
    void bubble_(size_t pos)
    {
        if(pos <= 1) return;

        const size_t f = pos/2;
        if(cmp_(arr_[pos], arr_[f])) {
            swap_(f, pos);
            bubble_(f);
        }
    }

    void sift_(size_t pos)
    {
        if(2*pos >= size_) return;

        if(2*pos+1 < size_) {
            size_t newPos = cmp_(arr_[2*pos], arr_[2*pos+1]) ? 2*pos : 2*pos+1;
            if(cmp_(arr_[newPos], arr_[pos])) {
                swap_(pos, newPos);
                sift_(newPos);
            }
        }
        else { // 2*pos+1 == size_
           if(cmp_(arr_[2*pos], arr_[pos]))
               swap_(pos, 2*pos);
        }
    }

    void swap_(size_t i , size_t j)
    {
        T tmp = arr_[i];
        arr_[i] = arr_[j];
        arr_[j] = tmp;
    }

    void print_(size_t pos, size_t step) const
    {
        if(pos >= size_) return;

        if(step > 0)
            std::cout << std::string(step-3, ' ') << std::string(3, '-');
        std::cout << arr_[pos] << std::endl;
        print_(2*pos, step+4);
        print_(2*pos+1, step+4);
    }
    size_t                  size_ = 1;
    std::vector<T>          arr_;
    const cmpType&          cmp_;
};

int main()
{
    auto larger = [](double v1, double v2) {return v1 > v2;};

    binary_heap<double, decltype(larger)>  bh(larger);
    bh.insert({3.1,8.9,2.1, 10.4, 11.2, 10.8, 2.5});
    bh.print();
    while(!bh.empty()) {
        auto min = bh.deleteMin();
        std::cout << "delete " << min << std::endl;
        bh.print();
    }
}
