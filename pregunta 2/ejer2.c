#include <stdio.h>

//suma
int sumar(int a, int b) {
    return a + b;
}

// resta
int restar(int a, int b) {
    return a - b;
}

// multiplicacion
int multiplicar(int a, int b) {
    return a * b;
}

// division
float dividir(int a, int b) {
    if (b != 0) {
        return (float) a / b;
    } else {
        printf("division entre cero.\n");
        return 0;
    }
}

int main() {
    int num1, num2;
    printf("ingrese un numero: ");
    scanf("%d", &num1);
    printf("ingrese un numero: ");
    scanf("%d", &num2);

    printf("Suma: %d\n", sumar(num1, num2));
    printf("Resta: %d\n", restar(num1, num2));
    printf("Multiplicacion: %d\n", multiplicar(num1, num2));
    printf("Division: %.2f\n", dividir(num1, num2));

    return 0;
}


