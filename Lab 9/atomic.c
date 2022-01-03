/** This program uses atomic for product sum of first 10 numbers * number of threads
 * Sai Suraj
 * 22/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
int main(int argc, char* argv[])
{
    // Use 4 threads when creating OpenMP parallel regions
    omp_set_num_threads(4);
 
    int total = 0;
 
    // Create the parallel region
    #pragma omp parallel default(none) shared(total)
    {
        for(int i=1; i <=10; i++)
        {
            // Atomically add i to the total
            #pragma omp atomic
            total+=i;
            printf("Thread implements %d\n", omp_get_thread_num()); 
        }
    }
 
    printf("Total = %d.\n", total);
 
    return EXIT_SUCCESS;
}

