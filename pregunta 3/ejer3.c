#include <stdio.h>
//en terminal gcc ejer3.c -o ejer3
//en terminal ./ejer3


void suma(float *a, float *b, float *resultado) {
    *resultado = *a + *b;
}

void resta(float *a, float *b, float *resultado) {
    *resultado = *a - *b;
}
void multiplicacion(float *a, float *b, float *resultado) {
    *resultado = *a * *b;
}

void division(float *a, float *b, float *resultado) {
    if (*b != 0) {
        *resultado = *a / *b;
    } else {
        printf("Error: División por cero no permitida.\n");
    }
}

int main() {
    float resultado,num1, num2;
    printf("ingrese un numero: ");
    scanf("%f", &num1);
    printf("ingrese un numero: ");
    scanf("%f", &num2);
    //suma
    suma(&num1, &num2, &resultado);
    printf("Suma: %.2f\n", resultado);

    // resta
    resta(&num1, &num2, &resultado);
    printf("Resta: %.2f\n", resultado);

    // mul
    multiplicacion(&num1, &num2, &resultado);
    printf("Multiplicación: %.2f\n", resultado);

    // div
    division(&num1, &num2, &resultado);
    if (num2 != 0) {
        printf("División: %.2f\n", resultado);
    }

    return 0;
}


