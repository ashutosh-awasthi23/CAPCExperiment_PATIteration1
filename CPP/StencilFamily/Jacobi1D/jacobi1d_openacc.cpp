#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    float A[N], B[N];

    for(int i=0;i<N;i++)
        A[i] = 1.0;

#pragma acc data copy(A) create(B)
{
    for(int t=0;t<iter;t++)
    {

#pragma acc parallel loop
        for(int i=1;i<N-1;i++)
            B[i] = 0.5*(A[i-1] + A[i+1]);

#pragma acc parallel loop
        for(int i=1;i<N-1;i++)
            A[i] = B[i];
    }
}

    cout<<"Done\n";
    return 0;
}