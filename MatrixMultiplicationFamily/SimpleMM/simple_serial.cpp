// ============================================================
//  Simple Matrix Multiplication — SERIAL
//  Compile : g++ -O2 -o simple_serial simple_serial.cpp
//  Run     : ./simple_serial <n>
// ============================================================
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

typedef vector<vector<double>> Matrix;

Matrix generateMatrix(int n) {
    Matrix M(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = (double)(rand() % 100) / 10.0;
    return M;
}

// C = A * B  (simple triple loop)
Matrix multiply(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

void printMatrix(const Matrix& M, const string& label, int n) {
    cout << label << " (" << n << "x" << n << "):\n";
    int show = (n <= 6) ? n : 4;   // print only first 4 rows/cols if large
    for (int i = 0; i < show; i++) {
        for (int j = 0; j < show; j++)
            printf("%8.2f ", M[i][j]);
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
    cout << "  Simple Matrix Multiplication  [SERIAL]\n";
    cout << "  n = " << n << "\n";
    cout << "==============================================\n\n";

    Matrix A = generateMatrix(n);
    Matrix B = generateMatrix(n);

    auto t1 = high_resolution_clock::now();
    Matrix C = multiply(A, B, n);
    auto t2 = high_resolution_clock::now();

    double ms = duration<double, milli>(t2 - t1).count();

    printMatrix(A, "Matrix A", n);
    printMatrix(B, "Matrix B", n);
    printMatrix(C, "Result C = A x B", n);

    printf("Time taken: %.4f ms\n\n", ms);
    return 0;
}
