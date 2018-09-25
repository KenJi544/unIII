
#include <mpi.h>
#include <stdio.h> 
int main(int argc, char *argv[]) 
{ 
   int size,size1,rank,namelen,t,incep=3; 
char processor_name[MPI_MAX_PROCESSOR_NAME];
   MPI_Comm parent; 
MPI_Status status;
   MPI_Init(&argc, &argv); 
   MPI_Comm_get_parent(&parent); 
MPI_Get_processor_name(processor_name,&namelen);
   if (parent == MPI_COMM_NULL) printf("No parent!\n");
   MPI_Comm_remote_size(parent, &size); 
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size1); 
   if (size != 1) printf("Something's wrong with the parent");  
 
   printf("Module '%s'. Start on the processor rank %d of the node name '%s'of world_size  %d \n",argv[0], rank,processor_name,size);
MPI_Barrier(MPI_COMM_WORLD);
if(rank==incep){
            MPI_Send(&rank,1,MPI_INT,(rank + 1) % size1,10,MPI_COMM_WORLD); 
            MPI_Recv(&t,1,MPI_INT, (rank+size1-1)%size1,10,MPI_COMM_WORLD,&status);
	}
	else{
            MPI_Recv(&t,1,MPI_INT, (rank+size1-1)%size1,10,MPI_COMM_WORLD,&status);
            MPI_Send(&rank,1,MPI_INT,(rank+1)%size1,10,MPI_COMM_WORLD); 
	}
  printf("==Module '%s'. proc num %d @%s rcvd=%d from %d\n",argv[0],rank, processor_name, t, t); 
   MPI_Finalize(); 
   return 0; 
} 
