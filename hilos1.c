#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct parametros{
    int inicio;
    int incremento;
    int id;
    int final;
}parametros;

void * secuencias(void * arg){
    parametros * philo = (parametros *) arg;
    int inicio = philo->inicio;
    int incremento = philo->incremento;
    int id = philo->id;
    int final = philo->final;
    int numero = inicio;
    while(numero < final){
        printf("\nSoy el hilo %d y el valor es: %d", id,numero);
        numero += incremento;
        // sleep(10);
    }
}

int main(){
    pthread_t hilo1, hilo2;    
    parametros philo1 = {1,1,1,10};
    parametros philo2 = {2,2,2,10};

    pthread_create (&hilo1, NULL, secuencias,(void *)&philo1);

    pthread_create (&hilo2, NULL, secuencias,(void *)&philo2);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);

    // sleep(10);
    printf("\nRegrese\n");
}