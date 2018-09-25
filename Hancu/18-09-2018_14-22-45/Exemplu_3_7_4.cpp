#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
int main(int argc, char** argv)
{
int rank, size, namelen, version, subversion, universe_size;
int globalrank,sumrank;
MPI_Comm family_comm,allcomm;
char processor_name[MPI_MAX_PROCESSOR_NAME],
worker_program[100];
int rank_from_child,ich;
MPI_Status status;
 MPI_Info hostinfo;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Get_processor_name(processor_name,&namelen);
MPI_Get_version(&version,&subversion);
printf("I'm manager %d of %d on %s running MPI %d.%d\n", rank, size, processor_name, version, subversion);
if (size != 1) printf("Error: Only one manager process should be running, but %d were started.\n", size);
universe_size = 12;
MPI_Info_create(&hostinfo);
MPI_Info_set(hostinfo, "host", "compute-0-1,compute-0-0,compute-0-3" );
strcpy(worker_program,"./HB_Woker_Comunication_V1.exe");
printf("Spawning %d worker processes running %s\n", universe_size-1, worker_program);
MPI_Comm_spawn(worker_program,MPI_ARGV_NULL,universe_size-1,hostinfo,0,MPI_COMM_SELF,&family_comm, MPI_ERRCODES_IGNORE);
  MPI_Intercomm_merge(family_comm,1,&allcomm);
  MPI_Comm_rank(allcomm, &globalrank);
  printf("manager: global rank is %d,rank is %d \n",globalrank,	rank);
  MPI_Allreduce(&globalrank,&sumrank,1,MPI_INT,MPI_SUM,allcomm);
  printf("sumrank after  allreduce  on  process  %d  is  %d  \n", rank,sumrank);
MPI_Comm_disconnect(&family_comm);
MPI_Finalize();
return 0;
}
