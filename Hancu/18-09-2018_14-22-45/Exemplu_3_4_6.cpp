/*====
In acest program se determina elementele maximale de pe liniile si coloanele unei matrici de dimensiuni arbitrare. Elementele matricei sunt initializate de procesul cu rankul 0. 
Se utilizeaza functia MPI_Reduce si operatiile MPI_MAX, MPI_MIN 
====*/
#include<mpi.h>
#include<stdio.h>
#include <iostream>
using namespace std;
void calculateSendcountsAndDispls(int rows, int cols, int size, int sendcounts[], int displs[])
{	
	int rowsPerProc = rows / size;
	int remainRows = rows % size;
	int currDispl = 0;
	for (int i = 0; i < size; ++i)
	{
		displs[i] = currDispl;
		if (i < remainRows)			
			sendcounts[i] = (rowsPerProc + 1) * cols;			
		else			
			sendcounts[i] = rowsPerProc * cols;
		currDispl += sendcounts[i];
	}	
}
void invertMatrix(double *m, int mRows, int mCols, double *rez)
{
	for (int i = 0; i < mRows; ++i)
		for (int j = 0; j < mCols; ++j)
			rez[j * mRows + i] = m[i * mCols + j];
}
void reduceLines(double* Rows, int reccount, int cols, double myReducedRow[], bool min)
{
	int myNrOfLines = reccount / cols;
	for (int i = 0; i < cols; ++i)			
	{
		double myMaxPerCol_i = Rows[i];
		for (int j = 1; j < myNrOfLines; ++j)
		{
			if (min)
			{
				if (Rows[j * cols + i] < myMaxPerCol_i)
					myMaxPerCol_i = Rows[j * cols + i];		
			} 
			else
			{
				if (Rows[j * cols + i] > myMaxPerCol_i)
					myMaxPerCol_i = Rows[j * cols + i];		
			}
		}
		myReducedRow[i] = myMaxPerCol_i;
	}
}
int main(int argc, char *argv[])
{
  	int size,reccount, source;
	double *A;
	int myrank, root=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int sendcounts[size], displs[size];
	int rows, cols;
	double *Rows;	
if (myrank ==0)
printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]);
//Procesul cu rankul root citeste dimensiunile matricii, aloca spatiul si initializeaza matricele
	if(myrank==root)
	{
		cout << "Introduceti nr. de rinduri a matricei: ";	
		cin >> rows;
		cout << "Introduceti nr. de coloane a matricei: ";
		cin >> cols;
	
		A=(double*)malloc(rows*cols*sizeof(double));
        for(int i=0;i<rows*cols;i++)
		  	A[i]=rand()/1000000000.0;
		printf("Tipar datele initiale\n");
		for(int i=0;i<rows;i++)
		{
			printf("\n");
			for(int j=0;j<cols;j++)
				printf("A[%d,%d]=%5.2f ",i,j,A[i * cols + j]);	
		}
		printf("\n");
		MPI_Barrier(MPI_COMM_WORLD);
	}
	else
		MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&rows, 1, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Bcast(&cols, 1, MPI_INT, root, MPI_COMM_WORLD);
	if (rows >= size)
	{		
		calculateSendcountsAndDispls(rows, cols, size, sendcounts, displs);
	}
	else
	{
		cout << "Introduceti un numar de linii >= nr de procese." << endl;
		MPI_Finalize();
		return 0;
	}	
	reccount = sendcounts[myrank];
	Rows = new double[reccount];
	MPI_Scatterv(A, sendcounts, displs, MPI_DOUBLE, Rows, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
if(myrank==root) cout << "Liniile matricei au fost repartizate astfel:" << endl;
	cout << "\nProces " << myrank << " - " << reccount / cols << " liniile" << endl;	
	MPI_Barrier(MPI_COMM_WORLD);
	double myReducedRow[cols];
	reduceLines(Rows, reccount, cols, myReducedRow, false);
	double* maxPerCols;
	if (myrank == root)
		maxPerCols = new double[cols];
MPI_Reduce(myReducedRow,maxPerCols,cols,MPI_DOUBLE,MPI_MAX,root,MPI_COMM_WORLD);
	if (myrank == root)
	{
		printf("\nValorile de maxim pe coloanele matricii sunt:\n");
		for (int i = 0; i < cols; ++i)		
			printf("Coloana %d - %.2f\n", i, maxPerCols[i]);	
			delete[] maxPerCols;			
	}
	double *invMatr;
	if (myrank == root)
	{
		invMatr = new double[cols * rows];
		invertMatrix(A, rows, cols, invMatr);
	}
	if (cols >= size)
	{
		calculateSendcountsAndDispls(cols, rows, size, sendcounts, displs);	
	}
	else
	{
		cout << "Introduceti un numar de coloane >= nr de procese." << endl;
		MPI_Finalize();
		return 0;
	}	
	reccount = sendcounts[myrank];
	delete[] Rows;
	Rows = new double[reccount];
	MPI_Scatterv(invMatr, sendcounts, displs, MPI_DOUBLE, Rows, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	double myReducedCol[rows];
	reduceLines(Rows, reccount, rows, myReducedCol, true);
	double* minPerRows;
	if (myrank == root)
		minPerRows = new double[rows];
	MPI_Reduce(myReducedCol,minPerRows,rows,MPI_DOUBLE,MPI_MIN,root,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myrank == root)
	{
		printf("\nValorile de minim pe liniile matricii sunt:\n");
		for (int i = 0; i < rows; ++i)		
			printf("Rindul %d - %.2f\n", i, minPerRows[i]);	
			delete[] minPerRows;			
	}
 	if (myrank == root)
	{
		free(A);
		}
	MPI_Finalize();
	delete[] Rows;
	return 0;
}
