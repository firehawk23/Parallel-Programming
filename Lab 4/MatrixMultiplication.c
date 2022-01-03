  /* This C Program is a Sequential code for Matrix Multiplication which uses file handling for both input and output.
   * Mukesh J
   * 07/09/2021
   * ***/


  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #include <omp.h>

  int** A;
  int** B;
  int** C;
  int N=0;

  // This function Allocates memory space to both MAtrix A and MAtrix B, Matrix C. It also takes input from file and stores into Matrix A, B.
  void initialize(FILE *fp)
  {  
	int i=0,j=0;  
        while(1)
        {
             A = malloc(sizeof(int*)*N);
             for(i=0; i<N; i++)
		      A[i] = malloc(sizeof(int)*N);
             if(A!= NULL)
                 break;
             else{
                 printf("\n Matrix A is not Allocated !!!\n");
                 return;     }
        }
        while(1)
        {
             B = malloc(sizeof(int*)*N);
             for(i=0; i<N; i++)
		      B[i] = malloc(sizeof(int)*N);
             if(B!= NULL)
                 break;
             else{
                 printf("\nMatrix B is not Allocated !!!\n");
                 return;     }
        }
        while(1)
        {
             C = malloc(sizeof(int*)*N);
             for(i=0; i<N; i++)
		      C[i] = malloc(sizeof(int)*N);
             if(C!= NULL)
                 break;
             else{
                 printf("\nMatrix C is not Allocated !!!\n");
                 return;     }
        }
	rewind(fp);
        for(i=0; i<N; i++)
	      for(j=0; j<N; j++)
              {
		     fscanf(fp,"%1d", &A[i][j]);
              }  
        for(i=0; i<N; i++)
	      for(j=0; j<N; j++)
              {
		     fscanf(fp,"%1d", &B[i][j]);
              }  
  }

  // This Function is used to Deallocate memory space of the Matrix A, B and Matrix C.
  void free_Space()
  {
        for(int i=0; i<N; i++)
		free(A[i]);
	free(A);
	for(int i=0; i<N; i++)
		free(B[i]);
	free(B);
	for(int i=0; i<N; i++)
		free(C[i]);
	free(C);
  }

  // This function is used to multiply the Matrix A and B and assign values in MAtrix C.
  void MatrixMultiply()
  {
      double start, end;
      start = omp_get_wtime();
      printf("Start: %f\t", start);
      for(int i=0; i<N; i++)
	  for(int j=0; j<N; j++)
          {
	      C[i][j]=0;
	      for(int k=0; k<N; k++)
		      C[i][j] += A[i][k]*B[k][j];
	  }
      end = omp_get_wtime();
      printf("End : %f\t Execution time : %f\n", end, end-start);
  }

  // This function is used to print Matrix C in output File.
  void printmatrix(FILE *fp) 
  {
	  //printf("\n");
	  fprintf(fp,"\n");
          for(int i=0; i<N; i++)
	  {
		  for(int j=0; j<N; j++)
		  {
	        	fprintf(fp,"%d ",C[i][j]);
                        //printf("%d ",board[i][j]);
                  }
		  fprintf(fp,"\n");
		  //printf("\n");
	  }
          fprintf(fp,"\n");
          //printf("\n");
    }

  // This is the Main function which takes care of File Handling and Command line arguments.
  void main(int argc, char *argv[])
  {
	FILE *fp; 
        FILE *fq;  
        fp = fopen(argv[1], "r");      // Input file is opened in Read mode.
	if (fp != NULL)
		printf("File found....!\n");
        else 
	{
		printf("Input file is not found.....\n");
		return ;
        }
	int row_count= 0;
	char* number =malloc(sizeof(char)*2048);   // Allocating memory space for string which is used to get input from file.

        while(fscanf(fp,"%s", number)!=EOF)
		row_count++;
        int i=0, j=0;
	N= row_count/2;
	//cols= strlen(number);
	printf("%d",N);  // %d, rows, cols);    // displays rows and cols in screen.
        fq = fopen("Matrixoutput", "w");   //  Output file is opened in write mode.
        if (fq != NULL) 
	  {
            fprintf(fq,"\n\t\tOutput File of Matrix Multiplication. \n");
            printf("\n\t\tOutput File of Matrix Multiplication \n");
        }
        else {
            printf("Failed to create a Writing file...\n");
            return ;
        }

        initialize(fp);
        fprintf(fq,"\nOutput Matrix C is \n");
        MatrixMultiply();
	printmatrix(fq);
        free_Space();
	fclose(fp);
	fclose(fq);
  }
 

