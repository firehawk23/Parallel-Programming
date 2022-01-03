#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

#define N 100
int main (int argc, char *argv[])
{

    double start,end;
    int array[N],i,count,num,randindex;
    omp_set_num_threads(3);
    FILE *fptr;
    fptr = fopen("A.txt", "w");


    #pragma  parallel
    {
      
    for(i=0;i<N;i++){
        array[i]= rand() % 100;
        fprintf(fptr, "%d ", array[i]);
    }
    int b[10];
    for(i=1;i<6;i++){
        randindex= (rand()+i)%100;
        b[i-1] = array[randindex];
    }

    for(i=0;i<5;i++){
        count = 0;
       
        num = b[i];
          start = omp_get_wtime();
#pragma omp for
        for(i=0;i<N;i++)
        {
            if(array[i]==num)
                count++;
        }

        printf("Occurrence of %d is: %d\n", num, count);

    }}
    end = omp_get_wtime() - start;
    printf("Time = %.6g\n",end);
    return 0;
}
