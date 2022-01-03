#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

#define N 1000
int main (int argc, char *argv[])
{

    double start,end;
    float array[N],num;
    int i,count,randindex;
    omp_set_num_threads(4);
    FILE *fptr;
    fptr = fopen("A.txt", "w");
    for(i=0;i<N;i++){
        array[i]= rand() % 100;
        fprintf(fptr, "%f ", array[i]);
    }
    float b[10];
    for(i=1;i<2;i++){
    randindex= (rand()+i)%100;
    b[i-1] = array[randindex];
    }
    start = omp_get_wtime();
    for(i=0;i<1;i++){
    count = 0;
    num = b[i];
    #pragma omp for
    for(i=0;i<N;i++)
    {
        if(array[i]==num)
            count++;
    }
    
    printf("Occurrence of %g is: %d\n", num, count);
    
    }
    end = omp_get_wtime() - start;
    printf("Time = %.6g\n",end);
    return 0;
}
