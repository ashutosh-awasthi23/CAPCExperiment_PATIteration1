// ============================================================
//  Block (Tiled) Matrix Multiplication — OpenACC PARALLEL
//  Compile : pgc++ -O2 -acc -Minfo=accel -o block_acc block_acc.cpp
//       OR : nvc++ -O2 -acc -Minfo=accel -o block_acc block_acc.cpp
//  Run     : ./block_acc <n> [block_size]   (default block=32)
// ============================================================
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <chrono>
using namespace std;
using namespace std::chrono;

double* generateMatrix(int n) {
    double* M = new double[n * n];
    for (int i = 0; i < n * n; i++)
        M[i] = (double)(rand() % 100) / 10.0;
    return M;
}

void printMatrix(const double* M, const string& label, int n) {
    cout << label << " (" << n << "x" << n << "):\n";
    int show = (n <= 6) ? n : 4;
    for (int i = 0; i < show; i++) {
        for (int j = 0; j < show; j++)
            printf("%8.2f ", M[i * n + j]);
        if (show < n) cout << " ...";
        cout << "\n";
    }
    if (show < n) cout << "  ...\n";
    cout << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <n> [block_size]\n";
        return 1;
    }
    int n  = atoi(argv[1]);
    int bs = (argc >= 3) ? atoi(argv[2]) : 32;
    if (n <= 0 || bs <= 0) { cerr << "n and block_size must be positive\n"; return 1; }

    srand(42);

    cout << "==============================================\n";
    cout << "  Block Matrix Multiplication  [OpenACC]\n";
    cout << "  n = " << n << "  |  block_size = " << bs << "\n";
    cout << "==============================================\n\n";

    double* A = generateMatrix(n);
    double* B = generateMatrix(n);
    double* C = new double[n * n]();

    auto t1 = high_resolution_clock::now();

    // ---- OpenACC tiled kernel ----
    // Copy A and B to device once; accumulate C on device, copy back at end.
    #pragma acc data copyin(A[0:n*n], B[0:n*n]) copyout(C[0:n*n])
    {
        // Outer tile loops run on host; inner loops are GPU kernels.
        for (int ii = 0; ii < n; ii += bs) {
            for (int jj = 0; jj < n; jj += bs) {
                for (int kk = 0; kk < n; kk += bs) {

                    int i_end = (ii + bs < n) ? ii + bs : n;
                    int j_end = (jj + bs < n) ? jj + bs : n;
                    int k_end = (kk + bs < n) ? kk + bs : n;

                    #pragma acc parallel loop collapse(2) present(A[0:n*n], B[0:n*n], C[0:n*n])
                    for (int i = ii; i < i_end; i++) {
                        for (int j = jj; j < j_end; j++) {
                            double sum = 0.0;
                            #pragma acc loop reduction(+:sum)
                            for (int k = kk; k < k_end; k++)
                                sum += A[i * n + k] * B[k * n + j];
                            #pragma acc atomic update
                            C[i * n + j] += sum;
                        }
                    }
                }
            }
        }
    }
    // ---- end kernel ----

    auto t2 = high_resolution_clock::now();
    double ms = duration<double, milli>(t2 - t1).count();

    printMatrix(A, "Matrix A", n);
    printMatrix(B, "Matrix B", n);
    printMatrix(C, "Result C = A x B (blocked)", n);

    printf("Time taken (incl. data transfer): %.4f ms\n\n", ms);

    delete[] A; delete[] B; delete[] C;
    return 0;
}
