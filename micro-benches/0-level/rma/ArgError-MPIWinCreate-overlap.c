#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * overlapping windows are forbidden. (line 22)
 */

#define N 10

int main(int argc, char *argv[]) {
  int rank, numProcs;
  int buffer[N];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Win win1, win2;

  MPI_Win_create(buffer, (N / 2) * sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win1);

  // overlapping window is forbidden (windows overlap as sizeof(int) > 1 )
  MPI_Win_create(buffer + N / 2, (N / 2) * sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win2);

  MPI_Win_free(&win1);
  MPI_Win_free(&win2);

  MPI_Finalize();

  return 0;
}
