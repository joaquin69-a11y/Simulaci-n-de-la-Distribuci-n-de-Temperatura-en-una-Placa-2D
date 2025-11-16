/*
  jacobi_mpi.c
  Versión: Lógica MPI básica para Semana 1
  - Inicializa MPI
  - El proceso raíz (rank 0) crea la malla completa y pone condiciones de frontera
  - Distribuye bloques de filas a cada proceso usando MPI_Scatterv
  - Cada proceso recibe su bloque y muestra un resumen (no se ejecuta Jacobi)
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int NX = 100, NY = 100;  // por defecto
    if (argc >= 3) {
        NX = atoi(argv[1]);
        NY = atoi(argv[2]);
    } else if (rank == 0) {
        printf("Uso: mpirun -np P ./jacobi_mpi NX NY\n");
        printf("Usando NX=%d NY=%d por defecto.\n", NX, NY);
    }

    double *global = NULL;

    if (rank == 0) {
        global = (double*) malloc(sizeof(double) * NX * NY);
        if (!global) {
            fprintf(stderr, "Error reservando memoria.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (int j = 0; j < NY; j++)
            for (int i = 0; i < NX; i++)
                global[i + j * NX] = 0.0;

        for (int i = 0; i < NX; i++) {
            global[i] = 100.0;
            global[i + (NY - 1) * NX] = 100.0;
        }
        for (int j = 0; j < NY; j++) {
            global[j * NX] = 100.0;
            global[(NX - 1) + j * NX] = 100.0;
        }

        printf("[root] Malla global inicializada (%dx%d).\n", NX, NY);
    }

    int *counts = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));

    int base_rows = NY / size;
    int rem = NY % size;

    for (int p = 0; p < size; p++) {
        int rows = base_rows + (p < rem ? 1 : 0);
        counts[p] = rows * NX;
    }

    displs[0] = 0;
    for (int p = 1; p < size; p++) {
        displs[p] = displs[p - 1] + counts[p - 1];
    }

    int recvcount = counts[rank];

    double *local = malloc(sizeof(double) * (recvcount > 0 ? recvcount : 1));

    MPI_Scatterv(global, counts, displs, MPI_DOUBLE,
                 local, recvcount, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    int local_rows = recvcount / NX;

    printf("[rank %d/%d] Recibí %d filas. Primeros valores: ", rank, size, local_rows);
    for (int k = 0; k < (recvcount > 3 ? 3 : recvcount); k++)
        printf("%.2f ", local[k]);
    printf("\n");

    free(local);
    free(counts);
    free(displs);
    if (rank == 0) free(global);

    MPI_Finalize();
    return 0;
}
