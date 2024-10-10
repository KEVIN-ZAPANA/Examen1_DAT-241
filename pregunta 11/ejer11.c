#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//terminal mpicc -o ejer11  ejer11.c
//terminal mpiexec -n 3 ./ejer11


int main(int argc, char *argv[]) {
    int rank, size, n = 10;
    int vector_a[10], vector_b[10], vector_resultante[10];
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicialización procesador 0
    if (rank == 0) {
        //aleatorios
        srand(42);  // Semilla
        for (i = 0; i < n; i++) {
            vector_a[i] = rand() % 10;
            vector_b[i] = rand() % 10;
        }

        //vectores a los procesadores 1 y 2
        MPI_Send(vector_a, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector_b, n, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(vector_a, n, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vector_b, n, MPI_INT, 2, 1, MPI_COMM_WORLD);
        int suma_impares[10], suma_pares[10];
        MPI_Recv(suma_impares, n/2, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(suma_pares, n/2 + n%2, MPI_INT, 2, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (i = 0; i < n; i++) {
            if (i % 2 == 0) {
                vector_resultante[i] = suma_pares[i/2];
            } else {
                vector_resultante[i] = suma_impares[i/2];
            }
        }

        // Imprimir
        printf("Vector A: ");
        for (i = 0; i < n; i++) printf("%d ", vector_a[i]);
        printf("\nVector B: ");
        for (i = 0; i < n; i++) printf("%d ", vector_b[i]);
        printf("\nVector Resultante: ");
        for (i = 0; i < n; i++) printf("%d ", vector_resultante[i]);
        printf("\n");

    } else if (rank == 1) {
        // Procesador 1 impares
        int vector_a[10], vector_b[10], suma_impares[5];
        MPI_Recv(vector_a, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector_b, n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 1; i < n; i += 2) {
            suma_impares[i/2] = vector_a[i] + vector_b[i];
        }
        MPI_Send(suma_impares, n/2, MPI_INT, 0, 2, MPI_COMM_WORLD);

    } else if (rank == 2) {
        // Procesador 2  pares
        int vector_a[10], vector_b[10], suma_pares[5];
        MPI_Recv(vector_a, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector_b, n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < n; i += 2) {
            suma_pares[i/2] = vector_a[i] + vector_b[i];
        }
        MPI_Send(suma_pares, n/2 + n%2, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}



