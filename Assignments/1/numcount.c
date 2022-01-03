#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

#define N 1000
int main()
{
    struct timeval start, stop;
    int array[N],i,count,num,randindex;
    FILE *fptr;
    fptr = fopen("A.txt", "w");
    for(i=0;i<N;i++){
        array[i]= rand() % 100;
        fprintf(fptr, "%d ", array[i]);
    }
randindex= rand() % 100;

    num = array[randindex];

    count = 0;
    gettimeofday(&start, 0);
    for(i=0;i<N;i++)
    {
        if(array[i]==num)
            count++;
    }
    gettimeofday(&stop, 0);
    printf("Occurrence of %d is: %d\n", num, count);
    fprintf(stdout, "Time = %.6f\n\n",(stop.tv_sec + stop.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6));
    return 0;
}
