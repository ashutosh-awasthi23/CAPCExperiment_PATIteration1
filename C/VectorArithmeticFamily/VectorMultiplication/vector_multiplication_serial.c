#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    float *A = malloc(n*sizeof(float));
    float *B = malloc(n*sizeof(float));
    float *C = malloc(n*sizeof(float));

    for(int i=0;i<n;i++){
        A[i] = i*1.0;
        B[i] = i*2.0;
    }

    for(int i=0;i<n;i++){
        C[i] = A[i] * B[i];
    }

    printf("Result sample: %f\n", C[n-1]);

    free(A); free(B); free(C);
    return 0;
}