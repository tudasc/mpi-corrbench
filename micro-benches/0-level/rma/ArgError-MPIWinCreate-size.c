#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * invalid window size must be non-negative (line 20)
 *
 */

#define N 10

int main(int argc, char *argv[]) {
  int rank, numProcs;
  int buffer[N];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Win win;

  MPI_Win_create(buffer, -1, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

  MPI_Win_free(&win);
  MPI_Finalize();

  return 0;
}
