#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    int i,j,t;

    float A[N][N], B[N][N];

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            A[i][j] = 1.0;

#pragma acc data copy(A) create(B)
{
    for(t=0;t<iter;t++)
    {

#pragma acc parallel loop collapse(2)
        for(i=1;i<N-1;i++)
            for(j=1;j<N-1;j++)
                B[i][j] = 0.25*(A[i-1][j] + A[i+1][j] +
                                A[i][j-1] + A[i][j+1]);

#pragma acc parallel loop collapse(2)
        for(i=1;i<N-1;i++)
            for(j=1;j<N-1;j++)
                A[i][j] = B[i][j];
    }
}

    printf("Done\n");
    return 0;
}