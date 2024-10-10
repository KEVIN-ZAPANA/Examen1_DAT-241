#include <stdio.h>
#include <omp.h>
#include <math.h>

// PARA HACER CORRER EN LA TERMINAL gcc -o ejer12 -fopenmp ejer12.c -lm

int main() {
    int n = 15;
    int fib[n];
    double phi = (1 + sqrt(5)) / 2;//nro aureo
    int i;

    // mis variables compartidas son fib y n y mi variable privada es i
    #pragma omp parallel for shared(fib, n) private(i)
    for (int i = 0; i < n; i++) {
        fib[i] = (int)((pow(phi, i) - pow(1 - phi, i)) / sqrt(5));
    }

    printf("Serie\n");
    for (int i = 0; i < n; i++) {
        printf("fib[%d] = %d\n", i, fib[i]);
    }

    return 0;
}

