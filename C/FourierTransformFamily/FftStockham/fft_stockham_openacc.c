#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793

int log2int(int n)
{
    int r=0;
    while(n>1){
        n>>=1;
        r++;
    }
    return r;
}

int main(int argc,char *argv[])
{
    if(argc!=2){
        printf("Usage: %s N\n",argv[0]);
        return 1;
    }

    int N=atoi(argv[1]);

    double *in_r=malloc(N*sizeof(double));
    double *in_i=malloc(N*sizeof(double));
    double *out_r=malloc(N*sizeof(double));
    double *out_i=malloc(N*sizeof(double));

    for(int i=0;i<N;i++){
        in_r[i]=i;
        in_i[i]=0;
    }

    int stages=log2int(N);

    for(int s=1;s<=stages;s++)
    {
        int m=1<<s;
        int half=m/2;

        #pragma acc parallel loop collapse(2)
        for(int k=0;k<N;k+=m)
        {
            for(int j=0;j<half;j++)
            {
                int even=k+j;
                int odd=k+j+half;

                double angle=-2*PI*j/m;

                double wr=cos(angle);
                double wi=sin(angle);

                double tr=wr*in_r[odd]-wi*in_i[odd];
                double ti=wr*in_i[odd]+wi*in_r[odd];

                out_r[even]=in_r[even]+tr;
                out_i[even]=in_i[even]+ti;

                out_r[odd]=in_r[even]-tr;
                out_i[odd]=in_i[even]-ti;
            }
        }

        double *tmp;

        tmp=in_r; in_r=out_r; out_r=tmp;
        tmp=in_i; in_i=out_i; out_i=tmp;
    }

    printf("Output sample: %f %f\n",in_r[N-1],in_i[N-1]);

    free(in_r);
    free(in_i);
    free(out_r);
    free(out_i);

    return 0;
}