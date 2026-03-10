#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);

    int i,j;

    float A[N][N], B[N][N], C[N][N];

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
        }

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            C[i][j] = A[i][j] * B[i][j];

    printf("Done\n");

    return 0;
}