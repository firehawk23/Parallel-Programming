#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

static long num_steps= 10000000000;
double step;
int main ()
{
struct timeval start, stop;
int i;
double x, pi, sum = 0.0;
gettimeofday(&start, 0);
step = 1.0/(double) num_steps;
for (i=0;i< num_steps; i++)
{
x = (i+0.5)*step;
sum = sum + 4.0/(1.0+x*x);
}
pi = step * sum;
gettimeofday(&stop, 0);
fprintf(stdout, "Time = %.6f\n\n",(stop.tv_sec + stop.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6));
return(0);
}
