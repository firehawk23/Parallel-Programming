#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
	int index;
	int i;
	int count;
	int first;
	int N;
	int prime;
	char *marked;
	double start, end;
	omp_set_num_threads(8);
	int n = 1000000;
	FILE *fptr;
	N = n+1;
	marked = (char *) malloc (N);
	if (marked==NULL){
		printf("Cannot allocate enough memory\n");
		exit(1);
	}
	for(i=0;i<N;i++){
	marked[i]=1;
	}
	marked[0]=0;
	marked[1]=0;
	index=2;
	prime=2;
	start = omp_get_wtime();
	# pragma omp parallel shared(n,marked),private(first)
	while(prime*prime<=n){
		first = 2*prime;
		#pragma omp parallel for
		for (i =first;i<N;i+=prime) marked[i]=0;
		while(!marked[++index]);
		prime=index;
	}
	# pragma omp barrier
	count=0;
	fptr = fopen("kPairs_1000000.txt", "w");
	#pragma omp parallel for reduction(+:count)
	for(i=3;i<N;i=i+2){
		if(marked[i]==1 && marked[i+2]==1){
		fprintf(fptr,"(%d,%d) \n",i,i+2);
		++count;
	      }
	}
	
	end = omp_get_wtime() - start;
	printf("n : %d , k : %d\n",n,count);
	printf("%.6g seconds\n",end);
	return 0;
}
