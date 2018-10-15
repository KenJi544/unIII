#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	srand(time(NULL));
  	int numtask, cols, sendcount, reccount, source;
	double * A;
	double * B;
	int i, myrank, root = 1;
	printf("\n ---> Enter the number of columns in matrix: ");
	while(1)
	{
		scanf("%d", &cols);
		if(numb_1 < 4)
		{
			printf("\n *** The number must be greater than 4! ***\n");
			printf("\n Enter another number: ");
		}
		else
			break;
	}
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtask);
	double ain[numtask], aout[numtask];
	int ind[numtask];
	struct {
		double val;
		int rank;
	} in[numtask], out[numtask];
	
	sendcount = numtask;
	reccount = numtask;
	if (myrank == root)
  	{
		printf("===== Rezultatele programului '%s' =====\n", argv[0]);
		A = (double *) malloc(numtask * cols * sizeof(double));
		B = (double *) malloc(numtask * cols * sizeof(double));
		for(int i = 0; i < numtask * cols; i++)
			A[i] = rand() / 1000.0;
			B[i] = rand() / 1000.0;
		printf("Tipar datele initiale\n");
		for(int i = 0; i < numtask; i++)
		{
			printf("\n");
			for(int j = 0; j < cols; j++)
				printf("A[%d,%d]=%.2f ", i, j, A[i*numtask+j]);
		}
		printf("\n");
		for(int i = 0; i < numtask; i++)
		{
			printf("\n");
			for(int j = 0; j < cols; j++)
				printf("A[%d,%d]=%.2f ", i, j, A[i*numtask+j]);
		}
		printf("\n");
		MPI_Barrier(MPI_COMM_WORLD);
	}
	else MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(A, sendcount, MPI_DOUBLE, ain, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);
	for (i = 0; i < numtask; ++i) 
	{
		in[i].val = ain[i];
		in[i].rank = myrank;
	}
	MPI_Reduce(in, out, numtask, MPI_DOUBLE_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);
	if (myrank == root) 
	{
		printf("\n");
		printf("Valorile maximale de pe coloane si indicele liniei:\n");
		for (i = 0; i < numtask; ++i) 
		{
			aout[i] = out[i].val;
			ind[i] = out[i].rank; 
			printf("Coloana %d, valoarea=  %.2f, linia= %d\n", i, aout[i], ind[i]); 
		}
	}
	MPI_Finalize();
	return 0;
}

/*
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpiCC -o Exemplu_3_4_7.exe Exemplu_3_4_7.cpp
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 6 -machinefile ~/nodes4  Exemplu_3_4_7.exe
===== Rezultatele programului 'Exemplu_3_4_7.exe' =====
Tipar datele initiale

A[0,0]=1.80 A[0,1]=0.85 A[0,2]=1.68 A[0,3]=1.71 A[0,4]=1.96 A[0,5]=0.42 
A[1,0]=0.72 A[1,1]=1.65 A[1,2]=0.60 A[1,3]=1.19 A[1,4]=1.03 A[1,5]=1.35 
A[2,0]=0.78 A[2,1]=1.10 A[2,2]=2.04 A[2,3]=1.97 A[2,4]=1.37 A[2,5]=1.54 
A[3,0]=0.30 A[3,1]=1.30 A[3,2]=0.04 A[3,3]=0.52 A[3,4]=0.29 A[3,5]=1.73 
A[4,0]=0.34 A[4,1]=0.86 A[4,2]=0.28 A[4,3]=0.23 A[4,4]=2.15 A[4,5]=0.47 
A[5,0]=1.10 A[5,1]=1.80 A[5,2]=1.32 A[5,3]=0.64 A[5,4]=1.37 A[5,5]=1.13 

Valorile maximale de pe coloane si indicele liniei:
Coloana 0, valoarea=  1.80, linia= 0
Coloana 1, valoarea=  1.80, linia= 5
Coloana 2, valoarea=  2.04, linia= 2
Coloana 3, valoarea=  1.97, linia= 2
Coloana 4, valoarea=  2.15, linia= 4
Coloana 5, valoarea=  1.73, linia= 3
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 8 -machinefile ~/nodes4  Exemplu_3_4_7.exe
===== Rezultatele programului 'Exemplu_3_4_7.exe' =====
Tipar datele initiale

A[0,0]=1.80 A[0,1]=0.85 A[0,2]=1.68 A[0,3]=1.71 A[0,4]=1.96 A[0,5]=0.42 A[0,6]=0.72 A[0,7]=1.65 
A[1,0]=0.60 A[1,1]=1.19 A[1,2]=1.03 A[1,3]=1.35 A[1,4]=0.78 A[1,5]=1.10 A[1,6]=2.04 A[1,7]=1.97 
A[2,0]=1.37 A[2,1]=1.54 A[2,2]=0.30 A[2,3]=1.30 A[2,4]=0.04 A[2,5]=0.52 A[2,6]=0.29 A[2,7]=1.73 
A[3,0]=0.34 A[3,1]=0.86 A[3,2]=0.28 A[3,3]=0.23 A[3,4]=2.15 A[3,5]=0.47 A[3,6]=1.10 A[3,7]=1.80 
A[4,0]=1.32 A[4,1]=0.64 A[4,2]=1.37 A[4,3]=1.13 A[4,4]=1.06 A[4,5]=2.09 A[4,6]=0.63 A[4,7]=1.66 
A[5,0]=1.13 A[5,1]=1.65 A[5,2]=0.86 A[5,3]=1.91 A[5,4]=0.61 A[5,5]=0.76 A[5,6]=1.73 A[5,7]=1.97 
A[6,0]=0.15 A[6,1]=2.04 A[6,2]=1.13 A[6,3]=0.18 A[6,4]=0.41 A[6,5]=1.42 A[6,6]=1.91 A[6,7]=0.75 
A[7,0]=0.14 A[7,1]=0.04 A[7,2]=0.98 A[7,3]=0.14 A[7,4]=0.51 A[7,5]=2.08 A[7,6]=1.94 A[7,7]=1.83 

Valorile maximale de pe coloane si indicele liniei:
Coloana 0, valoarea=  1.80, linia= 0
Coloana 1, valoarea=  2.04, linia= 6
Coloana 2, valoarea=  1.68, linia= 0
Coloana 3, valoarea=  1.91, linia= 5
Coloana 4, valoarea=  2.15, linia= 3
Coloana 5, valoarea=  2.09, linia= 4
Coloana 6, valoarea=  2.04, linia= 1
Coloana 7, valoarea=  1.97, linia= 5
[Hancu_B_S@hpc Notate_Exemple]$ 
*/

