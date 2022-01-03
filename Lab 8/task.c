/* This program display sum of n numbers using task construct in Parallel region.
 * Sai Suraj
 * 20/09/2021
 * */

#include <stdio.h>
#include <omp.h>

int sumn(int n)
{
	int i, j;
	if (n<2)
	     return n;
	else
        {
             #pragma omp task shared(i) firstprivate(n)     //  sumn is in parallel region. It's using 8 threads to work.
	     {
		 // printf("Task 1 is running with Thread number: %d \n",omp_get_thread_num());
		  i=sumn(n-1);
	     }	  

             #pragma omp task shared(j) firstprivate(n)     //  fib is in parallel region. It's using 8 threads to compute.
	     {
		  //printf("Task 2 is running with Thread number: %d \n",omp_get_thread_num());
		  j=sumn(n-2);
	     }	  

	     #pragma omp taskwait   // Waiting for both threads to return
	     return i+j;
	}
}

int main()
{
        int n = 10;
	omp_set_num_threads(8);
	#pragma omp parallel shared(n)
	{
	      #pragma omp single    // This line allows only one thread to go inside.
	      printf ("sum of %d elements = %d with Thread %d .\n", n, sumn(n),omp_get_thread_num());
	}
	return 0;
}
