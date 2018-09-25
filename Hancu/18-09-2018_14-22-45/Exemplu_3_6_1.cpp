#include <stdio.h>
#include <mpi.h>
#include <math.h>
double f(double a)
{
    return (4.0 / (1.0 + a*a));
}
int main(int argc, char *argv[]) 
{
double PI25DT = 3.141592653589793238462643;
int n, numprocs, myid, i,done = 0;
double mypi, pi, h, sum, x;
int  namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Win nwin, piwin;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&myid);
MPI_Get_processor_name(processor_name,&namelen);
	//===Crearea locatiilor de memorie pentru realizarea RMA  
if (myid==0){
     MPI_Win_create(&n,sizeof(int),1,MPI_INFO_NULL, MPI_COMM_WORLD, &nwin);
     MPI_Win_create(&pi,sizeof(double),1,MPI_INFO_NULL, MPI_COMM_WORLD, &piwin);
	    }
else {
     // procesele nu vor utiliza datele din memoria ferestrelor sale nwin si piwin 
     MPI_Win_create(MPI_BOTTOM, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &nwin);
     MPI_Win_create(MPI_BOTTOM, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &piwin);
     }
while (!done)
{
if (myid == 0) { printf("Enter the number of intervals: (0 quits):\n"); 
		fflush(stdout);
		scanf("%d",&n); 
		pi=0.0;
		}
//Procesele cu rank diferit de 0 "citesc" variabila n a procesului cu rank 0	
	MPI_Win_fence(0,nwin);
     if (myid != 0) 
	MPI_Get(&n, 1, MPI_INT, 0, 0, 1, MPI_INT, nwin);
	MPI_Win_fence(0,nwin);
if ( n == 0 ) done = 1;
else {       h = 1.0 / (double) n;
             sum = 0.0;
             for (i = myid + 1; i <= n; i += numprocs) { x = h * ((double)i - 0.5); sum += f(x);}
             mypi = h * sum;
             MPI_Win_fence(0, piwin);
             MPI_Accumulate(&mypi, 1,MPI_DOUBLE, 0, 0, 1,MPI_DOUBLE,MPI_SUM, piwin);
             MPI_Win_fence(0, piwin);
             if (myid == 0) {printf("For number of intervals %d pi is approximately %.16f, Error is %.16f\n ", n, pi, fabs(pi-PI25DT));
fflush(stdout); }
     }
}
MPI_Win_free(&nwin);
MPI_Win_free(&piwin);
MPI_Finalize();
return 0;
}
