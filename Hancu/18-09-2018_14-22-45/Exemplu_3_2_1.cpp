#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"         
int main(int argc,char *argv[])
{ 
int size,rank,namelen;
int local_rank = atoi(getenv("OMPI_COMM_WORLD_LOCAL_RANK"));
char processor_name[MPI_MAX_PROCESSOR_NAME];
 MPI_Status status;
  MPI_Init(&argc,&argv);                                       
  MPI_Comm_size(MPI_COMM_WORLD,&size);  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
sleep (rank);
if (rank ==0)
printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 
MPI_Barrier(MPI_COMM_WORLD);
  MPI_Get_processor_name(processor_name,&namelen);
if (local_rank == 0) {
printf("==Au fost generate %s MPI processes pe nodul %s ===\n", getenv("OMPI_COMM_WORLD_LOCAL_SIZE"), processor_name);
		     }
MPI_Barrier(MPI_COMM_WORLD);
if (rank ==0)
printf("==Procesele comunicatorului MPI_COMM_WORLD au fost 'distribuite' pe noduri astfel: \n"); 
MPI_Barrier(MPI_COMM_WORLD);
printf("Hello, I am the process number %d (local runk %d) on the compute hostname %s , from total number of  process %d\n",rank, local_rank,processor_name, size); 
   MPI_Finalize();                                                 
  return 0;                                                       
}
