#include <iostream>
#include <cmath>
#include <cstdlib>

#define PI 3.141592653589793

int log2int(int n)
{
    int r = 0;
    while (n > 1)
    {
        n >>= 1;
        r++;
    }
    return r;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " N\n";
        return 1;
    }

    int N = atoi(argv[1]);

    double *in_r = new double[N];
    double *in_i = new double[N];
    double *out_r = new double[N];
    double *out_i = new double[N];

    for (int i = 0; i < N; i++)
    {
        in_r[i] = i;
        in_i[i] = 0;
    }

    int stages = log2int(N);

    for (int s = 1; s <= stages; s++)
    {
        int m = 1 << s;
        int half = m / 2;

        #pragma acc parallel loop collapse(2)
        for (int k = 0; k < N; k += m)
        {
            for (int j = 0; j < half; j++)
            {
                int even = k + j;
                int odd = k + j + half;

                double angle = -2 * PI * j / m;

                double wr = cos(angle);
                double wi = sin(angle);

                double tr = wr * in_r[odd] - wi * in_i[odd];
                double ti = wr * in_i[odd] + wi * in_r[odd];

                out_r[even] = in_r[even] + tr;
                out_i[even] = in_i[even] + ti;

                out_r[odd] = in_r[even] - tr;
                out_i[odd] = in_i[even] - ti;
            }
        }

        std::swap(in_r, out_r);
        std::swap(in_i, out_i);
    }

    std::cout << "Output sample: " << in_r[N-1] << " " << in_i[N-1] << std::endl;

    delete[] in_r;
    delete[] in_i;
    delete[] out_r;
    delete[] out_i;

    return 0;
}