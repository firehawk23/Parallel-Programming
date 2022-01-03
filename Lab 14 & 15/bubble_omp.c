#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int SIZE =100;
	int A[SIZE];
	omp_set_num_threads(2);
	for(int i=0;i<SIZE;i++)
	{
	    A[i]=rand()%SIZE;
	}

	int N = SIZE;
	int i; 
	int first,temp;
	double start,end;
	start=omp_get_wtime();
	#pragma omp parallel for default(none),shared(A,N,first),private(temp,i)
	for( first = 0; first<N; first++ )
	{
		if (first%2 == 0){
			
			for(i=1;i<N;i+=2)
			{
			if( A[i-1]>A[i] )
			{
				temp = A[i-1];
				A[i-1] = A[i];
				A[i] = temp;
			}
		}
	}
		 
	else{	
		for(i=1;i<N-1;i+=2)
		{
			if( A[i] > A[i+1] )
			{
				temp = A[i+1];
				A[i+1] = A[i];
				A[i] = temp;
			}
		}
	     }
	}
end=omp_get_wtime()-start;
printf("\n Time Parallel= %f \n",end);
return 0;
}
