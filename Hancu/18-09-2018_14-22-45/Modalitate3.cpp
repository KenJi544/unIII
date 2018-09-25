#include <mpi.h>        /* MPI Library                                            */
	#include <omp.h>        /* OpenMP Library                                         */
	#include <stdio.h>      /* printf()                                               */
	#include <stdlib.h>     /* EXIT_SUCCESS                                           */

	int main (int argc, char *argv[]) {

	    /* Parameters of MPI.                                                         */
	    int M_N;                             /* number of MPI ranks                   */
	    int M_ID;                            /* MPI rank ID                           */
	    int rtn_val;                         /* return value                          */
	    char name[128];                      /* MPI_MAX_PROCESSOR_NAME == 128         */
	    int namelen;

	    /* Parameters of OpenMP.                                                      */
	    int O_P;                             /* number of OpenMP processors           */
	    int O_T;                             /* number of OpenMP threads              */
	    int O_ID;                            /* OpenMP thread ID                      */

	    /* Initialize MPI.                                                            */
	    /* Construct the default communicator MPI_COMM_WORLD.                         */
	    rtn_val = MPI_Init(&argc,&argv);

	    /* Get a few MPI parameters.                                                  */
	    rtn_val = MPI_Comm_size(MPI_COMM_WORLD,&M_N);    /* get number of MPI ranks   */
	    rtn_val = MPI_Comm_rank(MPI_COMM_WORLD,&M_ID);   /* get MPI rank ID           */
	    MPI_Get_processor_name(name,&namelen);
	    printf("Nume nod:%s   MPIrank:%d  Numar de MPI procese:%d\n", name,M_ID,M_N);

	    /* Get a few OpenMP parameters.                                               */
	    O_P  = omp_get_num_procs();          /* get number of OpenMP processors       */
	    O_T  = omp_get_num_threads();        /* get number of OpenMP threads          */
	    O_ID = omp_get_thread_num();         /* get OpenMP thread ID                  */
	    printf("Nume nod:%s   MPIrank:%d   OpenMP ID:%d  Numar de OpenMP proceseoare:%d  Numar de OpenMP fire:%d\n", name,M_ID,O_ID,O_P,O_T);

	    /* PARALLEL REGION                                                            */
	    /* Thread IDs range from 0 through omp_get_num_threads()-1.                   */
	    /* We execute identical code in all threads (data parallelization).           */
	    #pragma omp parallel private(O_ID)
	    {
	    O_ID = omp_get_thread_num();          /* get OpenMP thread ID                 */
	  //  MPI_Get_processor_name(name,&namelen);
	    printf("Regiune Paralela:       Nume nod:%s MPIrank=%d OpenMP ID=%d\n", name,M_ID,O_ID);
	    }

	    /* Terminate MPI.                                                             */
	    rtn_val = MPI_Finalize();

	    /* Exit master thread.                                                        */
	    printf("Nume nod:%s MPIrank:%d OpenMP ID:%d   Exits\n", name,M_ID,O_ID);
	    return EXIT_SUCCESS;
	}

