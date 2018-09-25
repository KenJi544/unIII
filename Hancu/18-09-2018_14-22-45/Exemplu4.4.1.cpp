/*
Se ilustreaza Modalitatea 1 de comunicare in programe mixte MPI-Openmp. Toate comunicarile sunt "controlate" de procesul MPI cu rankul 0. 
Se determina suma a doi vectori...
*/
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;
 
int main(int argc, char **argv)
{
        int rnk, sz, n, i,info;
        double *x, *y, *buff;
 
        //n = atoi(argv[1]);
n=100;
MPI_Init(&argc, &argv);
//       MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &info);
        MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
        MPI_Comm_size(MPI_COMM_WORLD, &sz);
 
        int chunk = n / sz;
        x = (double*)malloc(chunk *sizeof(double));
        y = (double*)malloc(chunk *sizeof(double));
 
        if(rnk == 0){
                buff = (double*)malloc(n *sizeof(double));;
				for(i = 0; i < n; i++)
                        buff[i] = (double) (i+2);
        }
                      
 
        MPI_Scatter(&buff[rnk*chunk], chunk, MPI_DOUBLE, x, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
 
        if(rnk == 0)
                for(i = 0; i < n; i++)
                        buff[i] = (double) (i*3);
 
        MPI_Scatter(&buff[rnk*chunk], chunk, MPI_DOUBLE, y, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
 
#pragma omp parallel for private(chunk) shared(x,y)
        for (i = 0; i < chunk; i++)
                x[i] = x[i] + y[i];
 
        MPI_Gather(x, chunk, MPI_DOUBLE, buff, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
 
        if(rnk == 0)
                for(i = 0; i<n; i++)
                        printf("x[%d] = %6.2f\n", i, buff[i]);
 
        MPI_Finalize();
        return 0;
}
