#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * overwriting the window handler (line 21)
 */

#define N 10

int main(int argc, char *argv[]) {
  int rank, numProcs;
  int buffer[N];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Win win1, win2;
  MPI_Win *w_handler = &win1;

  MPI_Win_create(buffer, (N / 2) * sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win1);

  if (argc == 1) {
    w_handler = &win1;
  } else {
    w_handler = &win2;
  }
  MPI_Win_create(&buffer[N / 2], (N / 2) * sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, w_handler);

  MPI_Win_free(&win1);
  MPI_Win_free(&win2);

  MPI_Finalize();

  return 0;
}
