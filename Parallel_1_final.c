#include <stdio.h>
#include <omp.h>



int main(int argc, char*argv[])
{


int numPartitions = 12000;
int circleCount = 0;
double a,b;


double interval = 0, pi = 0;
int i = 0, j = 0;
double start = omp_get_wtime( );
interval = 1.0/(double)numPartitions;
	
	#pragma omp parallel for private(a,b,j) reduction(+: circleCount)

	for (i = 0; i < numPartitions; i++) 
	{
	a = (i + .5)*interval;
	for (j = 0; j < numPartitions; j++) 
	{
	b = (j + .5)*interval;
	if ((a*a + b*b) <= 1) 
	circleCount++;
	}
	}
	
    
double end = omp_get_wtime( );
//double wtick = omp_get_wtick( );

    printf("start = %.16g\nend = %.16g\ndiff = %.16g\n",
             start, end, end - start);

   // printf_s("wtick = %.16g\n1/wtick = %.16g\n",
   //          wtick, 1.0 / wtick);
	
	printf("Value of circle count : %d \n", circleCount);
	pi = (double)(4*circleCount)/(numPartitions * numPartitions);
	printf("Estimate of pi is: %10.8lf\n", pi);
	return 0;
}

