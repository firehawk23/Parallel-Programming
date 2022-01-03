/**  This program uses all clauses like lastprivate, schedule, private, firstprivate, etc.. from loop Construct.
 *   Sai Suraj
 *   07/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    omp_set_num_threads(4);
    int Number = 123456;
    int Value = 456789;

    printf("\nThis Program used for Private, FirstPrivate, LastPrivate, Schedule, Reduction, Default and Shared clause.\n");
    int total = 0;
    int SIZE = 10;
    int* List = malloc(sizeof(int) * SIZE);
    if(List == NULL)
    {
        printf("Cannot allocate the List array.\n");
        return 0;
    }
    // Initialise the array
    for(int i = 0; i < SIZE; i++)
    {
        List[i] = (i+1)*(i+1);
    }
 
    // Calculate the sum of square of all elements in the Array.
    printf("\nFirstPrivate Clause variable:\tBefore Parallel Region : SIZE is %d.\n", SIZE);
    printf("\nPrivate Clause variable:\tBefore Parallel Region : Number is %d.\n", Number);
    printf("\nLastPrivate Clause:\tBefore Parallel Region : Value is %d.\n", Value);
    #pragma omp parallel for default(none) schedule(static,3) shared(List) firstprivate(SIZE) firstprivate(Value) private(Number) lastprivate(Value) reduction(+: total)
    for(int i = 0; i < SIZE; i++)
    {
        total += List[i];
        printf("Thread %d : Size is %d , Number is %d , Value is %d , Total is %d .\n", omp_get_thread_num(),SIZE, Number, Value, total);
    }
    printf("\n\tAfter Parallel Region : SIZE is %d.\n", SIZE);
    printf("\tAfter Parallel Region : Number is %d.\n", Number);
    printf("\tAfter Parallel Region : Value is %d.\n", Value);
    printf("\nIn FirstPrivate clause : The SIZE before Parallel region passed into Parallel region.");
    printf("\nIn Private Clause : The Number after Parallel region remains Unchanged.");
    printf("\nIn LastPrivate clause : The value inside Parallel region passed outside Parallel region.");
    printf("\n\nThe Sum of squared elements is  %d .\n", total);
    printf("\nIn Reduction Clause, Operator and Total variable corresponds to respective threads.\n\n");
    free(List); 
    return 0;
}

