/** This program uses barrier to print two statements
 * Sai Suraj
 * 22/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    //4 threads to create a parallel region
    omp_set_num_threads(4);
    // Create the parallel region
    #pragma omp parallel
    {
        // Threads print their first message
        printf("I print my first message : Thread %d\n", omp_get_thread_num()); 
        #pragma omp barrier

        #pragma omp single
        {
            printf("The barrier is complete.\n");
        }
 
        // Threads print their second message
        printf("I print my second message : Thread %d\n", omp_get_thread_num());
    }
 
    return 0;
}

