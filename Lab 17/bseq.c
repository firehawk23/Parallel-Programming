#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define n 3

int main(){
	FILE *fp,*af,*bf; //file pointer creation
	fp=fopen("seq.txt","w"); //write mode
	af=fopen("a.txt","r");
	bf=fopen("b.txt","r");
	int i,j,k;
	int mat[20][20],b[20];
	float sum=0.0,l[20][20]={0},u[20][20]={0},z[20]={0},x[20]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(af,"%d",&mat[i][j]);
	   }
	}
	//Display Your matrix in file
	fprintf(fp,"Matrix :\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fprintf(fp,"%d    ",mat[i][j]);
	   }
	   fprintf(fp,"\n");
	}
	//AX=B ,where B is the constant term
	for(i=0;i<n;i++){
		fscanf(bf,"%d\n",&b[i]);
	}
	
	//Display Your Constant Value
	fprintf(fp,"Constant Terms :\n");
	for(i=0;i<n;i++){
		fprintf(fp,"%d\n",b[i]);
	}
	
	for(i=0;i<n;i++){
		for(k=i;k<n;k++){
			sum=0;
			for(j=0;j<i;j++){
				sum+=l[i][j]*u[j][k];  //sum of terms
			}
			u[i][k]=mat[i][k]-sum;   //upper triangular method
		}
		//Lower matrix
		for(k=i;k<n;k++){
			if(i==k){
				l[i][i]=1;
			}
			else{
				sum=0;
				for(j=0;j<i;j++){
					sum+=l[k][j]*u[j][i];
				}
				l[k][i]=(mat[k][i]-sum)/u[i][i];      //Lower triangular method
			}
		}
	}
	
	fprintf(fp,"\nU:\n");   //Upper Traingualar Matrix
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fprintf(fp,"%f\t",u[i][j]);
		}
		fprintf(fp,"\n");
	}
	
	//Finding X in UX=Z       //Back substituition Method
	for(i=n-1;i>=0;i--){
		sum=0;
		for(j=n-1;j>i;j--){
			sum+=u[i][j]*x[j];
		}
		x[i]=(b[i]-sum)/u[i][i];
	//	printf("\nx[%d] : %f\n",i,x[i]);  
	}
	//Print X-->the soln 
	fprintf(fp,"\nThe Set of soln :\n");
	for (i=0;i<n;i++){
		fprintf(fp,"%f\n",x[i]);
	}
	fclose(fp);
	fclose(af);
	fclose(bf);
	return 0;
}
