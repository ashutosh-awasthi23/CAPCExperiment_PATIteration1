#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);

    float A[N][N], B[N][N], C[N][N];

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0.0;
        }

#pragma acc data copyin(A,B) copy(C)
{
#pragma acc parallel loop collapse(2)
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k=0;k<N;k++)
                C[i][j] += A[i][k] * B[k][j];
}

    cout<<"Done\n";
    return 0;
}