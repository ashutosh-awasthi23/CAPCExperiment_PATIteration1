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
            B[i][j] = 2.0;
        }

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            C[i][j] = A[i][j] * B[i][j];

    cout<<"Done\n";
    return 0;
}