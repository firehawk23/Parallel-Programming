#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
   int data=10, flag = 0;
   #pragma omp parallel num_threads(4)
   {
      if (omp_get_thread_num()%2==0) {
         data = 5;
         #pragma omp flush(flag, data)
         /* Set flag to release thread 1 */
         flag = 1;
         printf("flag=%d data=%d\n", flag, data);
         #pragma omp flush(flag)
      }
      else if (omp_get_thread_num()==1) {
         #pragma omp flush(flag, data)
         data = 15;
         printf("flag=%d data=%d\n", flag, data);
         #pragma omp flush(flag, data)
      }
      else{
        #pragma omp flush(flag, data)
      	printf("flag=%d data=%d\n", flag, data);
      	#pragma omp flush(flag)
      }
      printf("Thread %d : flag=%d data=%d\n",omp_get_thread_num(),flag, data);
   }
   return 0;
}
