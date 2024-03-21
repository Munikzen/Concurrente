#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM_ARR 10

int arr[TAM_ARR];

typedef struct rango{
    int inicio;
    int fin;
} rango;

void * calcularCuadrado(void * arg) {
    rango * argumentos = (rango *) arg;
    int inicio = argumentos->inicio;
    int fin = argumentos->fin;

    for (int i = inicio; i < fin; i++) {
        arr[i] = i * i;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilo1, hilo2;
    rango ran1, ran2;

    ran1.inicio = 0;
    ran1.fin = TAM_ARR / 2;
    ran2.inicio = TAM_ARR / 2;
    ran2.fin = TAM_ARR;

    pthread_create(&hilo1, NULL, calcularCuadrado, (void *)&ran1);
    pthread_create(&hilo2, NULL, calcularCuadrado, (void *)&ran2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    for (int i = 0; i < TAM_ARR; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
