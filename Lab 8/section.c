/**  This Program uses Parallel Sections
 *   Sai Suraj
 *   20/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
void function1()
{
    for (int i = 0; i <= 2; i++)
    {
          printf("\nSection 1 is executed by thread number : %d \n", omp_get_thread_num());
    }
}

void function2()
{
    for (int j = 0; j <= 3; j++)
    {
         printf("\nSection 2 is executed by thread number : %d \n", omp_get_thread_num());
    }
}

int main(int argc, char* argv[])
{    int n =10;
     int sum=0;

    // Use 4 threads when creating OpenMP parallel regions
    omp_set_num_threads(8);
    {  // Create the parallel sections
        #pragma omp parallel sections  
        {
	    #pragma omp section
            {
	        function1();
	    }
            #pragma omp section
	    {
	        function2();
	    }
	    
        }
        for (int i = 1; i <=n; ++i)
            sum += i;
    }
    printf("\n The Sum of first %d elements : %d.\n\n",n,sum);
    return 0;
}

