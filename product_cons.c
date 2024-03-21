#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int n = 10;
int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;

pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;


void * productor(void * arg){
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);
        while(count == BUFFER_SIZE){
            pthread_cond_wait(&cond_prod, &mutex);
        }

        count++;
        buffer[count] = i;
        printf("\nEL productor produce: %d", buffer[count]);
        // sleep(1);
        pthread_cond_signal(&cond_cons);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void * consumidor(void * arg){
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);

        while(count == 0){
            pthread_cond_wait(&cond_cons, &mutex);

        }

        count--;
        int item = buffer[count];
        printf("\nEL consumidor consume: %d", item);
        pthread_cond_signal(&cond_prod);
        pthread_mutex_unlock(&mutex);
        // sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t hiloProd, hiloCons;
    pthread_create(&hiloProd, NULL, productor, NULL);
    pthread_create(&hiloCons, NULL, consumidor, NULL);

    pthread_join(hiloProd, NULL);
    pthread_join(hiloCons, NULL);

    return 0;
}