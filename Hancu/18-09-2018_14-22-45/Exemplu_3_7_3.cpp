#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
int main(int argc, char** argv)
{
int rank, size, namelen, version, subversion, universe_size;
MPI_Comm family_comm;
char processor_name[MPI_MAX_PROCESSOR_NAME],
worker_program[100];
int rank_from_child,ich;
   MPI_Info hostinfo;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Get_processor_name(processor_name,&namelen);
MPI_Get_version(&version,&subversion);
printf("I'm manager %d of %d on %s running MPI %d.%d\n", rank, size, processor_name, version, subversion);
if (size != 1) printf("Error: Only one manager process should be running, but %d were started.\n", size);
universe_size = 12;
strcpy(worker_program,"./HB_Woker_Comunication.exe");
MPI_Info_create(&hostinfo);
MPI_Info_set(hostinfo, "host", "compute-0-1,compute-0-0,compute-0-3" );
printf("Spawning %d worker processes running %s\n", universe_size-1, worker_program);
MPI_Comm_spawn(worker_program,MPI_ARGV_NULL,universe_size-1,hostinfo,0,MPI_COMM_SELF,&family_comm, MPI_ERRCODES_IGNORE);
for(ich=0;ich<(universe_size-1);ich++)
{
  MPI_Recv(&rank_from_child,1,MPI_INT,ich,0,family_comm,MPI_STATUS_IGNORE);
 printf("Received rank %d from child %d \n",rank_from_child,ich);
}
MPI_Bcast(&rank,1,MPI_INT,MPI_ROOT,family_comm);
MPI_Comm_disconnect(&family_comm);
MPI_Finalize();
return 0;
}
