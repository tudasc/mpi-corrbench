#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * receive buffer is NULL on host. (line 16)
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum[2] = {1, 1};
  int *global_sum = NULL;

  MPI_Init(&argc, &argv);

  int root = 0;

  MPI_Scatter(local_sum, 1, MPI_INT, global_sum, 1, MPI_INT, root, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
