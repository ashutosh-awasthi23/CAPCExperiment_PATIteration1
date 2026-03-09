#include <iostream>
#include <cmath>
#include <cstdlib>

#define PI 3.141592653589793

void bit_reverse(double *real, double *imag, int N)
{
    int j = 0;

    for (int i = 1; i < N; i++)
    {
        int bit = N >> 1;

        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }

        j |= bit;

        if (i < j)
        {
            std::swap(real[i], real[j]);
            std::swap(imag[i], imag[j]);
        }
    }
}

void fft(double *real, double *imag, int N)
{
    bit_reverse(real, imag, N);

    for (int s = 2; s <= N; s *= 2)
    {
        int half = s / 2;
        double angle = -2 * PI / s;

        for (int k = 0; k < N; k += s)
        {
            for (int j = 0; j < half; j++)
            {
                double wr = cos(angle * j);
                double wi = sin(angle * j);

                int t = k + j + half;
                int u = k + j;

                double tr = wr * real[t] - wi * imag[t];
                double ti = wr * imag[t] + wi * real[t];

                real[t] = real[u] - tr;
                imag[t] = imag[u] - ti;

                real[u] += tr;
                imag[u] += ti;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " N\n";
        return 1;
    }

    int N = atoi(argv[1]);

    double *real = new double[N];
    double *imag = new double[N];

    for (int i = 0; i < N; i++)
    {
        real[i] = i;
        imag[i] = 0;
    }

    fft(real, imag, N);

    std::cout << "Output sample: " << real[N-1] << " " << imag[N-1] << std::endl;

    delete[] real;
    delete[] imag;

    return 0;
}