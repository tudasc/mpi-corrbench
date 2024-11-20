#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * win create is a collective operation and must be called by every rank. (line 20)
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
  if (rank == 0) {
    MPI_Win_create(buffer, N * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    MPI_Win_free(&win);
  }

  MPI_Finalize();

  return 0;
}
