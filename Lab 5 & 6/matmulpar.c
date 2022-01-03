#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4000

long long int a[N][N], b[N][N], c[N][N];

int main (int argc, char *argv[])
{
int	tid, nthreads, i, j, k;
double start,end;
FILE *fptr,*fptr1;

fptr = fopen("matA_4000.txt","r");
if(fptr==NULL){exit(1);}

fptr1 = fopen("matB_4000.txt","r");
if(fptr1==NULL){exit(1);}
/*** Create a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
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

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  start = omp_get_wtime();
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for
  for (i=0; i<N; i++)
    {
    //printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<N; j++)
      for (k=0; k<N; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** End of parallel region ***/
   end = omp_get_wtime() - start;
/*** Print results ***/
/*** printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<N; i++)
  {
  for (j=0; j<N; j++)
    printf("%lld  ", c[i][j]);
  printf("\n");
  }
printf("******************************************************\n");***/
printf("Time = %.6g\n",end);
return(0);
}
