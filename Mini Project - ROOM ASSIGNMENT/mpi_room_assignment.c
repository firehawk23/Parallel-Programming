
/* The following C code implements the room-assignment problem
 * Written By : Sai Suraj(21560) and Suvam Tamang(21561)
 * MTCS - 103(P) Mini - Project
 */

 ///////////////////////////////////////////////////////////////////// ALL THE HEADER FILES  //////////////////////////////////////////////////////////////////////////
 
 #include<stdio.h>
 #include<time.h>
 #include<stdlib.h>
 #include<time.h>
 #include<math.h>
 #include<mpi.h>

 ///////////////////////////////////////////////////////// ALL THE FUNCTIONS DEFINITIONS AND PROTOTYPE ////////////////////////////////////////////////////////////////
 
 float getRand(int min,int max);
 void getMatrix(int**,int);
 int check(int *,int );
 int contains(int * a, int p, int n);
 void genSolution(int * a, int n);
 int getCost(int **,int *,int );
 int* makeCopy(int *,int );
 int getCost(int **,int *,int);
 int room_assign(int **,int *,int *,int,int,int,int);
 void Free(int *,int *,int **,int );
 int getMin(int *a, int size);
 int getIndex(int *a,int size);

 //////////////////////////////////////////////////////////////////////////// MAIN FUNCTION //////////////////////////////////////////////////////////////////////////
 
 int main(int argc,char *argv[]){
	 int rank, np;
	 int cost = 0;
	 int *aux,*a,**D;
	 double elapsed_time;

	 MPI_Init(&argc, &argv);
	 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	 MPI_Comm_size(MPI_COMM_WORLD, &np);
	 
	 //Opening the file passed as command line arguments for writing out the results
         FILE *fp = fopen(argv[1],"w");
	 if (fp == NULL){
		 printf("Error in opening  file!\n");
		 exit(-1);
	 }
	 
         FILE *fq = fopen(argv[2],"a");
	 if (fp == NULL){
		 printf("Error in opening  file!\n");
		 exit(-1);
	 }
	 int nthreads = atoi(argv[3]);
         
	 int *results;
	 int newCost = 0;

	 MPI_Barrier(MPI_COMM_WORLD);
	 elapsed_time = -MPI_Wtime();
	 
	 // Here n signifies the number of students
	 for(int n=10; n<=100; n+=2){

	         //int n = 20;
		 a = (int *)calloc(n,sizeof(int));
	         D = (int **)calloc(n,sizeof(int *));
	         for(int i=0;i<n;i++){
			 D[i] = (int *)calloc(n,sizeof(int));
	         }

	         if ( rank == 0 ){

			 // Generating the dislike matrix
			 getMatrix(D,n);
	                 results = (int *)calloc(np,sizeof(int));

	         }

                 //Every process generates the initial random distribution
		 genSolution(a,n);

		 /*for(int i=0;i<n;i++){
			 printf("%d ",a[i]);
		 }
		 printf("\n");*/

		 //Making a copy of the input array for further requirements
	         aux = makeCopy(a,n);
            
	         //Broadcasting the Compatibility matrix to other processes
                 for (int i = 0; i < n; i++){
			 MPI_Bcast(D[i], n, MPI_INT, 0, MPI_COMM_WORLD);
	         }
                 
		 //Calculating the intial cost
	         cost = getCost(D,a,n);

	         //Every Process performs the room assignment and calculates the optimal cost it finds as newCost
                 newCost = room_assign(D,a,aux,cost,n,rank,nthreads);
	         //Free(a,aux,D,n);

		 //Gathering the new cost calculated by each process
		 MPI_Gather(&newCost, 1, MPI_INT, results, 1, MPI_INT, 0, MPI_COMM_WORLD);

		 //The master process finally writes the results to the output file
                 if(rank==0){
			fprintf(fp,"%d %d %d\n", n, cost , getMin(results, np));
		 }
		 
		 /*printf("\n");
		 int id = getIndex(results,np); 
		 if(rank==id){
			 for(int i=0;i<n;i++){
				 printf("%d ",a[i]);
			 }
		 }*/

	         Free(a,aux,D,n);
	 }

	 elapsed_time += MPI_Wtime();
	 if(rank==0){
              fprintf(fq,"%d %lf\n",np,elapsed_time);
	 }

	 //End of the MPI Program
         MPI_Finalize();		 
	 fclose(fp);
	 fclose(fq);
	 return 0;
 }
 /* End of the main program */

 /* Function Name : getIndex
  * Use : Returns the ID of the process containing the minimum value of the cost
  */

 int getIndex(int *a,int n){
	 int min = 0;
	 for(int j=1;j<n;j++){
		 if(a[j]<=min){
			 min = j;
		 }
	 }
	 return min;
 }

 /* Function Name : getMin
  * Use : iterates through the input array and returns the minimum element in it
  */

 int getMin(int *a, int size){
      int min = a[0];
      for(int j = 1; j<size; j++)
       	 if(a[j] <= min) 
		 min = a[j];
					
      return min;
 }

 /* Function Name : Free
  * Use : used for deallocating the storage used for storing arrays and matrices
  */

 void Free(int *a,int *aux,int **D,int n){
	 free(a);
	 free(aux);
	 for(int i=0;i<n;i++){
	    free(D[i]);}
	 free(D);
 }

 /* Function Name : getCost
  * Use : computes the total cost depending on the configuration of the input array and returns it
  */

 int getCost(int **D,int *a,int n){
	 int cost = 0;
	 for(int i=0;i<n;i++){
		 for(int j=0;j<n;j++){
			 if(a[i] == a[j]){
				 cost += D[i][j];
			 }
		 }
	 }
	 return cost;
 }

 /* Function Name : room_assign
  * Use : performs the permutation of students such that it results in the minimum possible cost and returns the cost
  */

 int room_assign(int **D,int *a,int *aux,int cost,int n,int rank,int nthreads){
         #pragma omp parallel num_threads(nthreads)
	 {
	    int temp;
	    float u1,u2;
	    int c1,c2;
	    int t=10;
	    srand(rank+time(0));
            
            #pragma omp for
	    for(int i=0;i<1000;i++){
	         while(1){
	             u1 = getRand(0,1);
	             u2 = getRand(0,1);
	             c1 = floor(u1*n);
	             c2 = floor(u2*n);
		     if(a[c1]!=a[c2]) break;
	         }
		 temp = aux[c1];
	         aux[c1] = aux[c2];
	         aux[c2] = temp;

		 int newCost = getCost(D,aux,n);
	         int delta = newCost-cost;
	         double expo = exp( (double) (-delta)/t);
	         double u = ((double)rand()/(RAND_MAX));
	 
	         if (delta < 0 || expo >= u ){
		    int t = a[c1];
	            a[c1] = a[c2];
	            a[c2] = t;
		    cost = newCost;
		    i = 0;
	         }
	         else{
		      temp = aux[c2];
	              aux[c2] = aux[c1];
	              aux[c1] = temp;
		      i = i + 1;
	         }
	         t = 0.999*t;
	     }
	 }
	 return cost;
  }

 /* Function Name : getRand
  * Use : returns an int between [min, max[
  */

 float getRand(int min, int max)
 {
   return (int) min + (rand() / (((double)RAND_MAX + 1)/ max));
 }

 /* Function Name : getMatrix
  * Use : forms the dislike matrix
  */

 void getMatrix(int **D,int size){
	 int num;
	 for(int i=0;i<size;i++){
		 for(int j=i;j<size;j++){
		     num = rand()%11;
		     D[i][j]=num;
		     D[j][i]=num;
                 }
	 }
 }
 
 /* Function Name : contains
  * Use : checking if the input array already contains a certain element
  */

 int contains(int * a, int p, int n)
 {
	 for(int i = 0; i<n; i++){
		if (a[i] == p) return 1;
         }
	 return 0;
 } 

 /* Function Name : genSolution
  * Use : generates a random solution
  */

 void genSolution(int * a, int n)
 {
    for(int i=0; i<n; i++){
	if(a[i] == 0)
	{
	    int p = rand() % (n/2) + 1;
            if( !contains(a, p, n) )
            {
          	a[i] = p;
		a[i+(n/2)] = p;
            }
            else i--;
        }
     }
  }

 /* Function Name : makeCopy
  * Use : used for making a copy of the input array and returning it
  */

 int* makeCopy(int *a,int n){
	 int *res = (int *)calloc(n,sizeof(int));
	 for(int i=0;i<n;i++){
		 res[i]=a[i];
	 }
	 return res;
 }

 ////////////////////////////////////////////////////////////////////////////// END //////////////////////////////////////////////////////////////////////////////////
