#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[])
{
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    float img[N][N], out[N][N];

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            img[i][j] = 1.0;

#pragma acc data copy(img) create(out)
{
    for(int t=0;t<iter;t++)
    {

#pragma acc parallel loop collapse(2)
        for(int i=1;i<N-1;i++)
            for(int j=1;j<N-1;j++)
                out[i][j] = (img[i-1][j] + img[i+1][j] +
                             img[i][j-1] + img[i][j+1] +
                             img[i][j]) / 5.0;

#pragma acc parallel loop collapse(2)
        for(int i=1;i<N-1;i++)
            for(int j=1;j<N-1;j++)
                img[i][j] = out[i][j];
    }
}

    cout<<"Done\n";
    return 0;
}