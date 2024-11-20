#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * invalid displacement unit (must be positive) (line 20)
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

  int disp_unit = 1;
  if (argc == 1) {
    disp_unit = -1;
  } else {
    disp_unit = 1;
  }

  MPI_Win_create(buffer, N, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

  MPI_Win_free(&win);

  MPI_Finalize();

  return 0;
}
