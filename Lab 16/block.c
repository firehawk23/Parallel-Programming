  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #include <omp.h>

  double** A;
  double** B;
  double** C;
  int N=0;

  // This function Allocates memory space to both MAtrix A and MAtrix B, Matrix C. It also takes input from file and stores into Matrix A, B.
  void initialize(FILE *fp)
  {  
	int i=0,j=0;  
        while(1)
        {
             A = malloc(sizeof(double*)*N);
             for(i=0; i<N; i++)
		      A[i] = malloc(sizeof(double)*N);
             if(A!= NULL)
                 break;
             else{
                 printf("\n Matrix A is not Allocated !!!\n");
                 return;     }
        }
        while(1)
        {
             B = malloc(sizeof(double*)*N);
             for(i=0; i<N; i++)
		      B[i] = malloc(sizeof(double)*N);
             if(B!= NULL)
                 break;
             else{
                 printf("\nMatrix B is not Allocated !!!\n");
                 return;     }
        }
        while(1)
        {
             C = malloc(sizeof(double*)*N);
             for(i=0; i<N; i++)
		      C[i] = malloc(sizeof(double)*N);
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
		     fscanf(fp,"%1le", &A[i][j]);
              }  
        for(i=0; i<N; i++)
	      for(j=0; j<N; j++)
              {
		     fscanf(fp,"%1le", &B[i][j]);
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


      void MM (int Crow, int Ccol, int Arow, int Acol, int Brow, int Bcol, int l, int m, int n)
      {          /* Corner of C block */ /* Corner of A block */ /* Corner of B block */  /* Block A is l x m */  /* Block B is m x n */  /* Block C is l x n */
          int lhalf[3], mhalf[3], nhalf[3]; /* Quadrant sizes  */
          int i, j, k; 
          double *Aptr, *Bptr, *Cptr; 
       //   double start, end;
       //   start = omp_get_wtime();
       //   printf("Start: %f\t", start);
          if (m * n > 250000000) {           /* B doesn't fit in cache-multiply blocks of A, B */
              lhalf[0] = 0; 
	      lhalf[1] = l/2; 
	      lhalf[2] = l - l/2;
	      mhalf[0] = 0; 
	      mhalf[1] = m/2; 
	      mhalf[2] = m - m/2;
	      nhalf[0] = 0; 
	      nhalf[1] = n/2; 
	      nhalf[2] = n - n/2;
	      for (i = 0; i < 2; i++)
		    for (j = 0; j < 2; j++)
			    for (k = 0; k < 2; k++)
				    MM (Crow+lhalf[i], Ccol+mhalf[j],
						    Arow+lhalf[i], Acol+mhalf[k],
						    Brow+mhalf[k], Bcol+nhalf[j],
						    lhalf[i+1], mhalf[k+1], nhalf[j+1]);
	  } 
	  else {                              /* B fits in cache - do standard multiply */
            for (i = 0; i < 1; i++)
	        for (j = 0; j < n; j++) {
		      Cptr = &C[Crow+i][Ccol+j];
		      Aptr = &A[Arow+i][Acol];
		      Bptr = &B[Brow][Bcol+j];
		      for (k = 0; k < m; k++) {
			      *Cptr += *(Aptr++) * *Bptr; 
			      Bptr += N;
		      }
  		}
	  }
      //end = omp_get_wtime();
      //printf("End : %f\t Execution time : %f\n", end, end-start);
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
	        	fprintf(fp,"%le ",C[i][j]);
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
        struct timeval start, end;
        fp = fopen(argv[1], "r");      // Input file is opened in Read mode.
	if (fp != NULL)
		printf("File found....!\n");
        else 
	{
		printf("Input file is not found.....\n");
		return ;
        }
	int row_count= 0;
	char* number =malloc(sizeof(char)*4096);   // Allocating memory space for string which is used to get input from file.

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
        gettimeofday(&start, 0);
        MM(0,0,0,0,0,0,N,N,N);
        gettimeofday(&end, 0);
        printf("Execution time : %f\n", (end.tv_sec + end.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6));
        printf("\nOutput Matrix C is \n");
	printmatrix(fq);
        free_Space();
	fclose(fp);
	fclose(fq);
  }
