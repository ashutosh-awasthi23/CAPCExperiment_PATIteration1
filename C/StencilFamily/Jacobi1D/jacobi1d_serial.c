#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    int i,t;

    float A[N], B[N];

    for(i=0;i<N;i++)
        A[i] = 1.0;

    for(t=0;t<iter;t++)
    {
        for(i=1;i<N-1;i++)
            B[i] = 0.5*(A[i-1] + A[i+1]);

        for(i=1;i<N-1;i++)
            A[i] = B[i];
    }

    printf("Done\n");
}