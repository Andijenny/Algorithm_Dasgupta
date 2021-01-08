#include <bits/stdc++.h>

int64_t multiply(int32_t x, int32_t y)
{
    if(y == 0) return 0;
    int64_t z = multiply(x, y/2);

    if(y & 0x01) // odd
        return x + 2*z;
    else // even
        return 2*z;
}

// x = y*q + r
void divide(int64_t x, int32_t y, int32_t& q, int32_t& r)
{
    if(x == 0) {
        q = 0, r = 0;
        return;
    }

    divide(x/2, y, q ,r);
    q = 2*q, r = 2*r;
    if(x & 0x01) r += 1;

    if(r >= y) {
        r -= y, q += 1;
    }
}

// x^y mod N
int32_t modexp(int32_t x, int32_t y, int32_t N)
{
   if(y == 0) return 1;

   int32_t z = modexp(x, y/2, N);

   if(y & 0x01)
       return x*z*z%N;
   else
       return z*z%N;
}

//greatest common divider
int32_t gcd(int32_t x, int32_t y)
{
    if(y == 0) return 1;
    return gcd(y, x%y);
}

// d = a*x + b*y
// tuple<int32_t, int32_t, int32_t> <x, y, d>
void extend_gcd(int32_t a, int32_t b, std::tuple<int32_t, int32_t, int32_t>& ret)
{
    if(b == 0) {
        std::get<0>(ret) = 1;
        std::get<1>(ret) = 0;
        std::get<2>(ret) = a;

        return;
    }

    extend_gcd(b, a%b, ret);
    double x = std::get<0>(ret);
    double y = std::get<1>(ret);
    double d = std::get<2>(ret);

    std::get<0>(ret) = y;
    std::get<1>(ret) = x - a/b*y;
    std::get<2>(ret) = d;
}

int main()
{
    using namespace std;
    cout << "13*12 = "  << multiply(13, 12) << endl;

    int32_t q, r;
    divide(158, 12, q, r);

    cout << "158/12 = "  <<q << "..." << r  << endl;

    cout << "2^345 % 31 = " << modexp(2, 345, 31) << endl;

    tuple<int32_t, int32_t, int32_t> val;
    extend_gcd(25, 11, val);
    cout << get<2>(val) <<  " = 25*(" << get<0>(val) << ") + 11*(" << get<1>(val) << ")" << endl;

    return 0;
}

