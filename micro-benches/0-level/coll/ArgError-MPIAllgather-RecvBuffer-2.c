#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * NULL pointer as recv Buffer in MPI_Allgather. line 17
 *
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum = 4;
  int *global_sum = NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  MPI_Allgather(&local_sum, 1, MPI_INT, global_sum, 1, MPI_INT, MPI_COMM_WORLD);

  if (myRank == 0) {
    printf("Result: %d", global_sum[0]);
  }

  MPI_Finalize();

  return 0;
}
