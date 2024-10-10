#include <mpi.h>
#include <stdio.h>
#include <string.h>

//terminal mpicc -o ejer13  ejer13.c
//terminal mpiexec -n 3 ./ejer11

#define N 10 // Tamaño del vector

int main(int argc, char *argv[]) {
    int rank, size;
    char vector[N][20];
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // procesador 0
    if (rank == 0) {
        // cadenas
        for (i = 0; i < N; i++) {
            sprintf(vector[i], "Cadena_%d", i);
        }

        MPI_Send(vector, N * 20, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector, N * 20, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    } 
    else if (rank == 1) {
        // Procesador 1 posiciones pares
        char recv_vector[N][20];
        MPI_Recv(recv_vector, N * 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Procesador 1: Desplegando posiciones pares:\n");
        for (i = 0; i < N; i += 2) {
            printf("Posición %d: %s\n", i, recv_vector[i]);
        }
    } 
    else if (rank == 2) {
        // Procesador 2 posiciones impares
        char recv_vector[N][20];
        MPI_Recv(recv_vector, N * 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Procesador 2: Desplegando posiciones impares:\n");
        for (i = 1; i < N; i += 2) {
            printf("Posición %d: %s\n", i, recv_vector[i]);
        }
    }

    MPI_Finalize();
    return 0;
}

