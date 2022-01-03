/*  This Sequential Program implements floyd's algorithm. This program takes inputfile as input in command line argument and gives execution time and input size in observation file as output.
 *  Mukesh - 21557
 *  26/10/2021
 *  */


   #include <stdio.h>
   #include<stdlib.h>
   #include<omp.h>

   #define INF 99999

   const int size ;
   void printMatrix(int **mat) 
   {
 	   int i,j;
	   for (int i = 0; i < size; i++) 
	   {
		   for (int j = 0; j < size; j++) 
		   {
			   if (mat[i][j] == 99999)
				   printf("%5s", "INF");
			   else
				   printf("%5d", mat[i][j]);
		   }
		   printf("\n");
	   }
   }

   int main(int argc,char **argv) 
   {
	   int rows, cols, i, j ,size;
	   char c[100002];
	   int block_size = 0;               
	   int** matrix;                                       
	   FILE* fp1;
	   fp1 = fopen(argv[1],"r");
	   fscanf(fp1,"%[^\n]",c);
	   size = atoi(c);
	   printf("\n I am here \n");
	   do 
	   {
		   matrix= malloc(sizeof(int*)*size);                   
		   for(i=0; i<size; i++)
			   matrix[i] = malloc(sizeof(int)*size);
	   }while(!matrix);
	   for(i=0;i<size;i++)
	   {	
		   for(j=0;j<size;j++)
		   {
			   fscanf(fp1,"%d",&matrix[i][j]);
		   }
	   }
	   int k;
	   double start_time = omp_get_wtime();
	   for (k = 0; k < size; k++) {
		   for (i = 0; i < size; i++) {
			   for (j = 0; j < size; j++) {
				   if (matrix[i][k] + matrix[k][j] < matrix[i][j])
					   matrix[i][j] = matrix[i][k] + matrix[k][j];
			   }
		   }
	   }

	   double end_time = omp_get_wtime();
	   double total_time = end_time-start_time;
	   FILE* file_pointer = fopen("SeqObservation","a+");
	   fprintf(file_pointer,"\nTime Taken : %f seconds \nSize : %d\n",total_time,size);
	   fclose(file_pointer);
	   for(i=0; i<size; ++i)
		   free(matrix[i]);
	   free(matrix);
	   return 0;
   }
	
