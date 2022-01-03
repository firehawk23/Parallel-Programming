#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

#define RANDLIMIT 15	/* Magnitude limit of generated randno.*/
#define N 500

long long int a[N][N];
long long int b[N][N];
long long int c[N][N];
	
int main(int argc, char *argv[])
{
	struct timeval start, stop;
	int i, j, k;
	FILE *fptr,*fptr1;
	/*int N;
	scanf("Enter size of the Matrix : %d",&N);*/


	/* generate matrices  */
	fptr = fopen("matA.txt", "w");
	fptr1 = fopen("matB.txt", "w");
	for (i = 0; i < N; i++){
	 for (j = 0; j < N; j++){
		a[i][j] = (rand()%RANDLIMIT);
		fprintf(fptr, "%lld ", a[i][j]);
		b[i][j] = (rand() % RANDLIMIT);
		fprintf(fptr1, "%lld ", b[i][j]);
		c[i][j] = 0;

	 }
	 fprintf(fptr, "\n");
	 fprintf(fptr1, "\n");
	}
	fclose(fptr);
	fclose(fptr1);

#ifdef PRINT
	/* print matrices */
	printf("Matrix A:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d\t", a[i][j]);}
		printf("\n");
	}

	printf("Matrix B:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d\t", b[i][j]);}
		printf("\n");
	}

	printf("Matrix C:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d\t", c[i][j]);}
		printf("\n");
	}
#endif

	gettimeofday(&start, 0);

	for (j = 0; j< N; j++) {
		for (i = 0; i< N; i++) {
			for (k = 0; k < N; k++)
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
		} /* end j loop */
	} /* end i loop */

	gettimeofday(&stop, 0);

#ifdef PRINT
	/* print results*/
	/*printf("Answer c:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d\t", c[i][j]);}
		printf("\n");
	} */
#endif
	fprintf(stdout, "Time = %.6f\n\n",(stop.tv_sec + stop.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6));
	return(0);
}








