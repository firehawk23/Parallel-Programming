#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 500

long long int a[N][N], b[N][N], c[N][N],c1[N][N],c2[N][N],c3[N][N],c4[N][N],c5[N][N];

int main (int argc, char *argv[])
{
omp_set_num_threads(4);
    int	tid, nthreads, i, j, k;
    double start,end,start1,end1,start2,end2,start3,end3,start4,end4,start5,end5;
    FILE *fptr,*fptr1;

    fptr = fopen("matA_500.txt","r");
    if(fptr==NULL){exit(1);}

    fptr1 = fopen("matB_500.txt","r");
    if(fptr1==NULL){exit(1);}
/*** Create a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        #pragma omp single 
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n",nthreads);
            printf("Initializing matrices...\n");
        }
        /*** Initialize matrices ***/
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                fscanf(fptr,"%lld",&a[i][j]);
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                fscanf(fptr1,"%lld",&b[i][j]);
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c[i][j]= 0;
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c1[i][j]= 0;
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c2[i][j]= 0;
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c3[i][j]= 0;
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c4[i][j]= 0;
            }
        }
#pragma omp for
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                c5[i][j]= 0;
            }
        }
        start = omp_get_wtime();
#pragma omp for
        for (i=0; i<N; i++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(j=0; j<N; j++)
                for (k=0; k<N; k++)
                    c[i][j] += a[i][k] * b[k][j];
        }
        /*** End of parallel region ***/

        end = omp_get_wtime() - start;
        start1 = omp_get_wtime();
#pragma omp for
        for (j=0; j<N; j++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(k=0; k<N; k++)
                for (i=0; i<N; i++)
                    c1[i][j] += a[i][k] * b[k][j];
        }
        /*** End of parallel region ***/

        end1 = omp_get_wtime() - start1;
        start2 = omp_get_wtime();
#pragma omp for
        for (k=0; k<N; k++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(j=0; j<N; j++)
                for (i=0; i<N; i++)
                    c2[i][j] += a[i][k] * b[k][j];
        }
        /*** End of parallel region ***/

        end2 = omp_get_wtime() - start2;
        start3 = omp_get_wtime();
#pragma omp for
        for (k=0; k<N; k++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(i=0; i<N; i++)
                for (j=0; j<N; j++)
                    c3[i][j] += a[i][k] * b[k][j];
        }
        /*** End of parallel region ***/

        end3 = omp_get_wtime() - start3;
        start4 = omp_get_wtime();
#pragma omp for
        for (j=0; j<N; j++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(k=0; k<N; k++)
                for (i=0; i<N; i++)
                    c4[i][j] += a[i][k] * b[k][j];
        }
        /*** End of parallel region ***/

        end4 = omp_get_wtime() - start4;
        start5 = omp_get_wtime();
#pragma omp for
        for (i=0; i<N; i++)
        {
            //printf("Thread=%d did row=%d\n",tid,i);
            for(k=0; k<N; k++)
                for (j=0; j<N; j++)
                    c5[i][j] += a[i][k] * b[k][j];
        }}
    /*** End of parallel region ***/

    end5 = omp_get_wtime() - start5;
    /*printf("Result Matrix:\n");
     for (i=0; i<N; i++)
     {
         for (j=0; j<N; j++)
             printf("%lld  ", c1[i][j]);
         printf("\n");
     }

     printf("******************************************************\n");
      printf("Result Matrix:\n");
     for (i=0; i<N; i++)
     {
         for (j=0; j<N; j++)
             printf("%lld  ", c2[i][j]);
         printf("\n");
     }

     printf("******************************************************\n");*/
    printf("N : %d\n",N);
    printf("%.6g\n",end);
    printf("%.6g\n",end1);
    printf("%.6g\n",end2);
    printf("%.6g\n",end3);
    printf("%.6g\n",end4);
    printf("%.6g\n",end5);

    return(0);
}
