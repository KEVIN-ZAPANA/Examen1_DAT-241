#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 3  // matriz N x N

//la N tiene que ser divisible entre el numero de procesos

//PARA HACER CORRER EN LA TERMINAL mpicc -o ejer14 ejer14.c
//PARA HACER CORRER EN LA TERMINAL mpirun -np 3 ./ejer14
// el numero de procesos es el numero que va despeus de -np en la terminal

void imprimir_matriz(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int rango, tamano;
    int A[N][N], B[N][N], C[N][N];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamano);

    // matrices en el proceso principal (rango 0)
    if (rango == 0) {
    	printf("las matrices son de tamano N = %d. Ingrese los valores:\n", N);
        printf("Ingrese matriz A NxN:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &A[i][j]);
            }
        }
        printf("Ingrese matriz B NxN:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &B[i][j]);
            }
        }
    }
    
    // matriz B a los procesos
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    int filas_por_proceso = N / tamano;
    int inicio_fila = rango * filas_por_proceso;
    int fin_fila = (rango == tamano - 1) ? N : inicio_fila + filas_por_proceso;

    // matriz A a cada proceso
    int local_A[filas_por_proceso][N];
    if (rango == 0) {
        for (int i = 1; i < tamano; i++) {
            int fila_inicio = i * filas_por_proceso;
            MPI_Send(&A[fila_inicio][0], filas_por_proceso * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
        for (int i = 0; i < filas_por_proceso; i++) {
            for (int j = 0; j < N; j++) {
                local_A[i][j] = A[i][j];
            }
        }
    } else {
        MPI_Recv(&local_A, filas_por_proceso * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    int local_C[filas_por_proceso][N];
    for (int i = 0; i < filas_por_proceso; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }
    if (rango == 0) {
        for (int i = 0; i < filas_por_proceso; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = local_C[i][j];
            }
        }
        for (int i = 1; i < tamano; i++) {
            int fila_inicio = i * filas_por_proceso;
            MPI_Recv(&C[fila_inicio][0], filas_por_proceso * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("matriz final C:\n");
        imprimir_matriz(C);
    } else {
        MPI_Send(&local_C, filas_por_proceso * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}




