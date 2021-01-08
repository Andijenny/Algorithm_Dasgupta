#include <bits/stdc++.h>

using namespace std;
using namespace std::complex_literals;
#define M_PI           3.14159265358979323846

template<typename T>
void fftImpl(const vector<T>& arr, complex<double> w, vector<complex<double>>& fr)
{

    if(arr.size() == 1) {
        fr[0] = arr[0];
        return;
    }
    size_t n = arr.size()/2;

    vector<T> arrEven(n);
    vector<T> arrOdd(n);

    for(size_t i = 0; i < n; ++i) {
        arrEven[i] = arr[2*i];
        arrOdd[i] = arr[2*i+1];
    }

    vector<complex<double>> frEven(n);
    vector<complex<double>> frOdd(n);
    fftImpl(arrEven, w*w, frEven);
    fftImpl(arrOdd, w*w, frOdd);

    for(size_t j = 0; j < n; ++j) {
        auto omega = pow(w, j);
        fr[j] = frEven[j] + omega*frOdd[j];
        fr[j+n] = frEven[j] - omega*frOdd[j];
    }
}

//coeff.size() : power of 2, padding zero if not enough
void fft(const vector<double>& coeff, vector<complex<double>>& fourier)
{
    const size_t n = coeff.size();
    size_t base = 2;
    while((n/base > 0) && (n != base)) base *= 2;
    vector<double> coeffPaddingZeros(base, 0);
    copy(coeff.begin(), coeff.end(), coeffPaddingZeros.begin());

    fourier.resize(base);
    complex<double> w = cos(2*M_PI/base) + sin(2*M_PI/base)*1i;
    fftImpl(coeffPaddingZeros, w, fourier);
}

void ifft(const vector<complex<double>>& fr, vector<complex<double>>& coeff)
{
    const size_t n = fr.size();

    coeff.resize(n);
    complex<double> w = cos(2*M_PI/n) + sin(2*M_PI/n)*1i;
    fftImpl(fr, complex<double>(1.0, 0.0)/w, coeff);
}

int main()
{
    vector<double> coeff({0,  16879,  20522,  32766,  13475,  15341, -15341, -13475,
       -32766, -20522, -16879,      0,  16879,  20522,  32766,  13475,
        15341, -15341, -13475, -32766, -20522, -16879,      0,  16879,
        20522,  32766,  13475,  15341, -15341, -13475, -32766, -20522,
       -16879,      0,  16879,  20522,  32766,  13475,  15341, -15341,
       -13475, -32766, -20522, -16879,      0,  16879,  20522,  32767,
        13475,  15341, -15341, -13475, -32766, -20522, -16879,      0,
        16879,  20522,  32766,  13475,  15341, -15341, -13475, -32766,
       -20522, -16879,      0,  16879,  20522,  32766,  13475,  15341,
       -15341, -13475, -32767, -20522, -16879,      0,  16879,  20522,
        32766,  13475,  15341, -15341, -13475, -32766, -20522, -16879});

    vector<complex<double>> fr;
    fft(coeff, fr);
    cout << "omega/rad, Amt.\n";
    for(size_t i = 0; i < fr.size(); ++i) {
        cout << 2*M_PI/fr.size()*i << ", " << abs(fr[i]) << "\n";
    }
    cout << endl;

    vector<complex<double>> ifr;
    ifft(fr, ifr);
    cout << "raw, ifft\n";
    for(size_t i = 0; i < coeff.size(); ++i)
        cout << coeff[i] << ", " << ifr[i].real()/ifr.size() << "\n";
    cout << endl;
    return 0;
}
