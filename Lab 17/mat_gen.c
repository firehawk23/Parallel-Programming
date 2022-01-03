#include <stdio.h>
#include <stdlib.h>
#define n 500

int main() {
	unsigned short i, j;
    FILE *a,*b;
    a=fopen("a.txt","w");
    b=fopen("b.txt","w");
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
    		fprintf(a,"%d ", rand()%10);
    	}
    	fprintf(a,"\n");
    }
    
    for(i = 0; i < n;i++) {
    		fprintf(b,"%d\n", rand()%20);
    	}
	return 0;
}
