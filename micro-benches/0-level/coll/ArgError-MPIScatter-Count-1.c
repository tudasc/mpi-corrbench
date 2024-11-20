#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * Scatter attempts to read out of bounds. (line 17)
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum[2] = {1, 1};
  int global_sum[2] = {0, 0};

  MPI_Init(&argc, &argv);

  int root = 0;

  MPI_Scatter(local_sum, 2, MPI_INT, &global_sum, 2, MPI_INT, root, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
