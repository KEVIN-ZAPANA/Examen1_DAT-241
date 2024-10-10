#include <stdio.h>

// iterativa
void iterativo(int iteraciones, double *pi) {
    double sumatoria = 0.0;
    int signo = 1;
    
    for (int i = 0; i < iteraciones; i++) {
        double termino = signo * (1.0 / (2 * i + 1));
        sumatoria += termino;
        *pi = 4.0 * sumatoria;
        printf("Nro %d:  Pi = %.15f\n", i + 1, *pi);
        
        signo *= -1; // signo
    }
}

// recursiva
void recursivo(int iteraciones, int actual, double sumatoria, double *pi) {
    if (actual == iteraciones) {
        *pi = 4.0 * sumatoria; // puntero
        return;
    }
    // serie
    double termino = (actual % 2 == 0 ? 1.0 : -1.0) / (2 * actual + 1);
    double valorPi = 4.0 * (sumatoria + termino);
    printf("Nro %d: Pi = %.15f\n", actual + 1, valorPi);
    // Llamada recursiva
    recursivo(iteraciones, actual + 1, sumatoria + termino, pi);
}

int main() {
    int iteraciones;
    double piIte = 0.0;
    double piRe = 0.0;
    printf("nro de iteraciones: ");
    scanf("%d", &iteraciones);
    // iterativa
    printf("\nPi de manera iterativa:\n");
    iterativo(iteraciones, &piIte);
    //recursiva
    printf("\n Pi de manera recursiva:\n");
    recursivo(iteraciones, 0, 0.0, &piRe);
    return 0;
}


