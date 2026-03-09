#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    int i,j,t;

    float img[N][N], out[N][N];

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            img[i][j] = 1.0;

    for(t=0;t<iter;t++)
    {
        for(i=1;i<N-1;i++)
            for(j=1;j<N-1;j++)
                out[i][j] = (img[i][j] + img[i-1][j] +
                             img[i+1][j] + img[i][j-1] +
                             img[i][j+1]) / 5.0;

        for(i=1;i<N-1;i++)
            for(j=1;j<N-1;j++)
                img[i][j] = out[i][j];
    }

    printf("Done\n");
}