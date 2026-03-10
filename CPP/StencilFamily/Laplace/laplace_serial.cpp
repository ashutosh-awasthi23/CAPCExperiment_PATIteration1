#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    float A[N][N], B[N][N];

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            A[i][j] = 1.0;

    for(int t=0;t<iter;t++)
    {
        for(int i=1;i<N-1;i++)
            for(int j=1;j<N-1;j++)
                B[i][j] = 0.25*(A[i-1][j] + A[i+1][j] +
                                A[i][j-1] + A[i][j+1]);

        for(int i=1;i<N-1;i++)
            for(int j=1;j<N-1;j++)
                A[i][j] = B[i][j];
    }

    cout<<"Done\n";
}