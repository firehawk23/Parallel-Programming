/**  This Program uses Sections Construct with Private, FirstPrivate, LastPrivate, Reductions and Nowait.
 *   Sai Suraj
 *   07/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
void function1()
{
    for (int i = 0; i <= 4; i++)
    {
	  printf("\n Hello world!");
          printf("\nSection 1 is executed by thread number : %d \n", omp_get_thread_num()+1);
    }
}

void function2()
{
    for (int j = 0; j <= 3; j++)
    {
	 printf("\n\t\tCoding is awesome!");
         printf("\nSection 2 is executed by thread number : %d \n", omp_get_thread_num()+1);
    }
}

int main(int argc, char* argv[])
{    int n =5;
     int a[5]={'1','3','5','7','9'};
     int b[5]={'2','4','6','8','2'};
     int sum=0;

    // Use 4 threads when creating OpenMP parallel regions
    omp_set_num_threads(4);
    // Create the parallel region
    #pragma omp parallel default(none) shared(a, b,sum), firstprivate(n)
    {  // Create the sections
        #pragma omp sections  
        {
	    #pragma omp section
            {
	        function1();
	    }
            #pragma omp section
	    {
	        function2();
	    }
	    #pragma omp section
            {
	        function1();
	    }
            #pragma omp section
	    {
	        function2();
	    }
        }
        #pragma omp for nowait reduction(+:sum)
        for (int i = 0; i < 5; ++i)
            sum += a[i] + b[i];
    }
    printf("\n The Sum of all elements in Arrays are %d.\n\n",sum);
    return 0;
}

