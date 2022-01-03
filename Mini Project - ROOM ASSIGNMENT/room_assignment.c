
 /* The following C code implements the room-assignment problem
  * Written By : Sai Suraj(21560) and Suvam Tamang(21561)
  * MTCS - 103(P) Project
  */

 /* Declaring all the header files used */
 #include<stdio.h>
 #include<time.h>
 #include<stdlib.h>
 #include<time.h>
 #include<math.h>
 #include<omp.h>

 /* All the function prototypes used in the entire program */
 float getRand(int min,int max);
 void getMatrix(int**,int);
 int check(int *,int );
 int contains(int * a, int p, int n);
 void genSolution(int * a, int n);
 int getCost(int **,int *,int );
 int* makeCopy(int *,int );
 int getCost(int **,int *,int);
 int room_assign(int **,int *,int *,int,int,int);
 void Free(int *,int *,int **,int );

 /* Function : main function
  * The Driver Code
  */

 int main(int argc,char *argv[]){
	 
	 int cost = 0;
	 int n;
	 int *aux,*a,**D;
	 int newCost = 0;

	 //Output File to be written taken from the command line argument itself
         FILE *fp = fopen(argv[1],"w");
	 if(fp==NULL){
		 printf("Error!\n");
		 exit(-1);
	 }
         FILE *fq = fopen(argv[2],"a");
	 if(fq==NULL){
		 printf("Error!\n");
		 exit(-1);
	 }

	 //Number of threads to be used taken from the command line itself
         int t = atoi(argv[3]);

	 double start = omp_get_wtime();
	 //Here variable n signifies the total number of students 
	 for(n=10;n<=100;n+=2){
	
	    //Initially all the students will be randomly allocated to the available rooms	 
	    a = (int *)calloc(n,sizeof(int));
            genSolution(a,n);
	    
	    //Creating the dislike matrix
	    D = (int **)calloc(n,sizeof(int *));
	    for(int i=0;i<n;i++){
		 D[i] = (int *)calloc(n,sizeof(int));
	    }
            
            getMatrix(D,n);
	    
	    //Same as 'array a' used in calculations below
	    aux = makeCopy(a,n);

	    //Computing the initial cost
	    cost = getCost(D,a,n);
            
	    //Only two students can't arrange them, they have to be in the same room
	    if ( n == 2 ){  
		    newCost = cost;
	            fprintf(fp,"%d %d %d\n",n,cost,newCost);
		    continue;
	    }
            else{
		   //the room assign method performs the necessary computations and returns the final new cost 
                   newCost = room_assign(D,a,aux,n,cost,t);

	           fprintf(fp,"%d %d %d\n",n,cost,newCost);
	    }

	    Free(a,aux,D,n);
	 }
         double end = omp_get_wtime();
	 fprintf(fq,"%d %lf\n",t,end-start);

	 fclose(fq);
	 fclose(fp);
	 return 0;
 }
 /* End of the main program */

 /* Function Name : Free
  * Use : For deallocation of memory used for arrays and matrices before
  * Returns : NIL
  */
 
 void Free(int *a,int *aux,int **D,int n){
	 free(a);
	 free(aux);
	 for(int i=0;i<n;i++){
	    free(D[i]);}
	 free(D);
 }

  /* Function Name : room_assign
   * Use : used for permutation of the rooms of the students such that it results in the minimum output cost
   * Returns : overall cost
   */

  int room_assign(int **D,int *a,int *aux,int n,int cost,int nt){
          
	  //double start = omp_get_wtime();
	  //The pseducode given in the prescribed text book has been understood and then implemented here
	  //Start of the parallel section
          #pragma omp parallel num_threads(nt)
	  {
	    int temp;
	    float u1,u2;
	    int c1,c2;
	    int t=1;
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
		    int flag = a[c1];
	            a[c1] = a[c2];
	            a[c2] = flag;
		    cost = newCost;
		    i = 0;
	         }
	         else{
		      int fl = aux[c2];
	              aux[c2] = aux[c1];
	              aux[c1] = fl;
		      i = i + 1;
	         }
	         t = 0.999 * t;
	     }
	   }
           //double end = omp_get_wtime();
	   //printf("Size : %d Time Taken : %lf\n",n,end-start);
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
  * Use : used for the purpose of generating a symmetric matrix with entries between 0 and 10 both inclusive
  * Returns : void, matrix accessed as pass by reference
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
  * Use : checks whether an input array already contains the element sent or not
  * Returns : 1(if present) and 0(if not present)
  */

 int contains(int * a, int p, int n)
 {
	 for(int i = 0; i<n; i++){
		if (a[i] == p) return 1;
         }
	 return 0;
 } 
 
 /* Function Name : genSolution
  * Use : performs a random permutation of students in the available rooms and returns the array
  * Returns : arrays accessed as pass by reference
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

 /* Function Name : getCost
  * Use : calculating the total cost of the configuration given
  * Returns : the total cosr
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

 /* Function Name : makeCopy
  * Use : used for making  a copy of the input array
  * Returns : the copy version of the input array
  */

 int* makeCopy(int *a,int n){
	 int *res = (int *)calloc(n,sizeof(int));
	 for(int i=0;i<n;i++){
		 res[i]=a[i];
	 }
	 return res;
 }
