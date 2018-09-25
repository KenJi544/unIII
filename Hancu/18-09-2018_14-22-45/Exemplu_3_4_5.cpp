/*====
In acest program se determina elementele maximale de pe coloanele unei matrici patrate (dimensiunea este egala cu 
numarul de procese). Elementele matricei sunt initializate de procesul cu rankul 0.
Se utilizeaza functia MPI_Reduce si operatia MPI_MAX 
====*/
#include<mpi.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
int numtask,sendcount,reccount,source;
double *A,*Max_Col;
int i, myrank, root=0;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
MPI_Comm_size(MPI_COMM_WORLD, &numtask);
double Rows[numtask];	
sendcount=numtask;
reccount=numtask;
	if(myrank==root)
	{
    printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 
	A=(double*)malloc(numtask*numtask*sizeof(double));
    Max_Col=(double*)malloc(numtask*sizeof(double));
	for(int i=0;i<numtask*numtask;i++)
  	A[i]=rand()/1000000000.0;
	printf("Tipar datele initiale\n");
	for(int i=0;i<numtask;i++)
	{
	printf("\n");
	for(int j=0;j<numtask;j++)
	printf("A[%d,%d]=%5.2f ",i,j,A[i*numtask+j]);
	}
	printf("\n");
	MPI_Barrier(MPI_COMM_WORLD);
	}
	else MPI_Barrier(MPI_COMM_WORLD);
MPI_Scatter(A,sendcount,MPI_DOUBLE,Rows,reccount,MPI_DOUBLE,root,MPI_COMM_WORLD);
MPI_Reduce(Rows,Max_Col,numtask,MPI_DOUBLE,MPI_MAX,root,MPI_COMM_WORLD);
if (myrank==root) {
for(int i=0;i<numtask;i++)
       {
         printf("\n");
         printf("Elementul maximal de pe coloana %d=%5.2f ",i,Max_Col[i]);
        }
        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD); }
        else MPI_Barrier(MPI_COMM_WORLD);  
 MPI_Finalize();
return 0;
}
