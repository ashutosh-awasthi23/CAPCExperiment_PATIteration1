#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);

    int i, j, k;

    float A[N][N], B[N][N], C[N][N];

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0.0;
        }

#pragma acc data copyin(A,B) copy(C)
{
#pragma acc parallel loop collapse(2)
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            for(k=0;k<N;k++)
                C[i][j] += A[i][k] * B[k][j];
}

    printf("Done\n");

    return 0;
}