#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define iteraciones 1000000

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int balance = 0;

void *suma(void * arg){
    for (int i = 0; i < iteraciones; ++i){
        pthread_mutex_lock(&mutex1);
        balance +=1;
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}

void *resta(void * arg){
    for (int i = 0; i < iteraciones; ++i){
        pthread_mutex_lock(&mutex1);
        balance -=1;
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}


int main (){
    pthread_t sumador, restador;
    pthread_create(&sumador, NULL, suma, NULL);
    pthread_create(&restador, NULL, resta, NULL);

    pthread_join(sumador,NULL);
    pthread_join(restador,NULL);
    printf("\nEl valor balanceado es: %d", balance);

}

