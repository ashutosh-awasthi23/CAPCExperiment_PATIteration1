#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " N\n";
        return 1;
    }

    int N = atoi(argv[1]);

    double *A = new double[N];
    double *B = new double[N];
    double *C = new double[N];

    for(int i=0;i<N;i++){
        A[i] = i;
        B[i] = 2*i;
    }

    #pragma acc parallel loop
    for(int i=0;i<N;i++){
        C[i] = A[i] * B[i];
    }

    std::cout << "Result sample: " << C[N-1] << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}