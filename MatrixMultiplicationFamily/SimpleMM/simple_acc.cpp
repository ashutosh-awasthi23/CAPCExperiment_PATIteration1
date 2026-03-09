// ============================================================
//  Simple Matrix Multiplication — OpenACC PARALLEL
//  Compile : pgc++ -O2 -acc -Minfo=accel -o simple_acc simple_acc.cpp
//       OR : nvc++ -O2 -acc -Minfo=accel -o simple_acc simple_acc.cpp
//  Run     : ./simple_acc <n>
// ============================================================
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Use flat 1-D arrays for best OpenACC performance
// Access element (i,j) as  M[i*n + j]

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
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) { cerr << "n must be positive\n"; return 1; }

    srand(42);

    cout << "==============================================\n";
    cout << "  Simple Matrix Multiplication  [OpenACC]\n";
    cout << "  n = " << n << "\n";
    cout << "==============================================\n\n";

    double* A = generateMatrix(n);
    double* B = generateMatrix(n);
    double* C = new double[n * n]();   // zero-initialised

    auto t1 = high_resolution_clock::now();

    // ---- OpenACC kernel ----
    #pragma acc parallel loop collapse(2) copyin(A[0:n*n], B[0:n*n]) copyout(C[0:n*n])
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            #pragma acc loop reduction(+:sum)
            for (int k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
    }
    // ---- end kernel ----

    auto t2 = high_resolution_clock::now();
    double ms = duration<double, milli>(t2 - t1).count();

    printMatrix(A, "Matrix A", n);
    printMatrix(B, "Matrix B", n);
    printMatrix(C, "Result C = A x B", n);

    printf("Time taken (incl. data transfer): %.4f ms\n\n", ms);

    delete[] A; delete[] B; delete[] C;
    return 0;
}
