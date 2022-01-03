/* This program finds  number of threads*(sum of n elements) using critical construct in parallel region. This can be used instead of reduction in RaceConditions.
 * Sai Suraj
 * 20/09/2021
 * */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
int main(int argc, char* argv[])
{
     omp_set_num_threads(8);	          
     int total = 0;
     #pragma omp parallel default(none) shared(total)
     {
	    int my_value = 1;
	    int n = 10;
	    for(int i = 2; i <= n; i++)
	    {
	         my_value += i;
	    }
	    #pragma omp critical
	    {
	         printf("[Thread %d] Total before I add my value (%d): %d.\n", omp_get_thread_num(), my_value, total);
	         total += my_value;
	         printf("[Thread %d] Total after I added my value: %d.\n", omp_get_thread_num(), total);
	    }
	    printf("Product of Sum of first %d numbers and %d Threads is %d. \n",n,omp_get_num_threads(),total);
     }
     
     return 0;
}
