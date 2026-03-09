// ============================================================
//  Block (Tiled) Matrix Multiplication — SERIAL
//  Compile : g++ -O2 -o block_serial block_serial.cpp
//  Run     : ./block_serial <n> [block_size]   (default block=32)
// ============================================================
#include <iostream>
#include <vector>
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

// Block / tiled multiplication (serial)
void blockMultiply(const double* A, const double* B, double* C, int n, int bs) {
    // Zero out C
    for (int i = 0; i < n * n; i++) C[i] = 0.0;

    for (int ii = 0; ii < n; ii += bs)
        for (int jj = 0; jj < n; jj += bs)
            for (int kk = 0; kk < n; kk += bs)
                // Multiply block
                for (int i = ii; i < min(ii + bs, n); i++)
                    for (int k = kk; k < min(kk + bs, n); k++) {
                        double a_ik = A[i * n + k];
                        for (int j = jj; j < min(jj + bs, n); j++)
                            C[i * n + j] += a_ik * B[k * n + j];
                    }
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
    cout << "  Block Matrix Multiplication  [SERIAL]\n";
    cout << "  n = " << n << "  |  block_size = " << bs << "\n";
    cout << "==============================================\n\n";

    double* A = generateMatrix(n);
    double* B = generateMatrix(n);
    double* C = new double[n * n]();

    auto t1 = high_resolution_clock::now();
    blockMultiply(A, B, C, n, bs);
    auto t2 = high_resolution_clock::now();

    double ms = duration<double, milli>(t2 - t1).count();

    printMatrix(A, "Matrix A", n);
    printMatrix(B, "Matrix B", n);
    printMatrix(C, "Result C = A x B (blocked)", n);

    printf("Time taken: %.4f ms\n\n", ms);

    delete[] A; delete[] B; delete[] C;
    return 0;
}
