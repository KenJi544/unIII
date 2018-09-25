/* =====
Transmiterea mesajelor pe cerc incepand cu procesul "incep ".
Valoarea variabilei "incep" este initializata de procesul cu rankul 0.
=====*/
#include<stdio.h>
#include <iostream>
#include<mpi.h>
using namespace std;
int main(int argc,char *argv[])
{ 
  int size,rank,t,namelen,incep;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Status status; 
  MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Get_processor_name(processor_name,&namelen);
if (rank ==0)
printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 
  while (true) {
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
      cout << "Introduceti incep (de la 0 la " << size - 1 << ", sau numar negativ pentru a opri programul): ";
      cin >> incep;
    }
    MPI_Bcast(&incep, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (incep < 0) {
      MPI_Finalize();
      return 0;
    }
    if (size <= incep) {
      if (rank == 0) {
        cout << "Incep trebuie sa fie mai mic decit nr de procesoare (" << size - 1 << ").\n"/8 ==;
      }
      continue;
    }
    if(rank==incep){
      MPI_Send(&rank,1,MPI_INT, (rank + 1) % size, 10, MPI_COMM_WORLD);
      MPI_Recv(&t,1,MPI_INT, (rank+size-1) % size,10,MPI_COMM_WORLD,&status);
    }
    else{
      MPI_Recv(&t,1,MPI_INT, (rank+size-1)%size,10,MPI_COMM_WORLD,&status);
      MPI_Send(&rank,1,MPI_INT,(rank+1)%size,10,MPI_COMM_WORLD);
    }
    printf("Procesu cu rancul %d al nodului '%s' a primit valoarea %d de la procesul cu rancul %d\n",rank, processor_name, t, t);
  }
  MPI_Finalize();
  return 0;
}