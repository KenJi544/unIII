/* manager */ 
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) 
{ 
   int world_size, universe_size, *universe_sizep, flag, err[4],namelen,rank; 
   MPI_Comm everyone;           /* intercommunicator */ 
   char worker_program[100]="./HB_MPI_Spawn_Worker.exe"; 
   char processor_name[MPI_MAX_PROCESSOR_NAME];
   MPI_Info hostinfo;
char *host =(char*)"host";
   MPI_Init(&argc, &argv); 
MPI_Get_processor_name(processor_name,&namelen);
   MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 
 if (world_size != 1)  printf("Top heavy with management"); 

  MPI_Attr_get(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE,&universe_sizep, &flag);  
   if (!flag) { 
        printf("This MPI does not support UNIVERSE_SIZE. How many n processes total?\n"); 
        scanf("%d", &universe_size); 
             } else universe_size = *universe_sizep; 
   if (universe_size == 1)  printf("No room to start workers"); 
MPI_Info_create(&hostinfo);
MPI_Info_set(hostinfo, host, "compute-0-1,compute-0-0,compute-0-3" );
//MPI_Info_set(hostinfo, "add-hostfile", "nodes6" );
    universe_size=9;
 MPI_Comm_spawn(worker_program, MPI_ARGV_NULL, universe_size-1,hostinfo,0,MPI_COMM_WORLD, &everyone,err);  
     printf("===I am Manager ('%s'), run on the node '%s' with rank %d and generate %d proceses that run the program '%s' ===\n",argv[0],processor_name,rank,universe_size-1,worker_program);        
   MPI_Finalize(); 
   return 0; 
} 
