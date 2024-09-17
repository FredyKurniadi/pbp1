#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_ITERATIONS 1000000

int shared_data = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Seksi kritis tanpa sinkronisasi (berpotensi race condition)
        shared_data++;
    }
    return NULL;
}

void* increment_with_lock(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Seksi kritis dengan sinkronisasi menggunakan mutex
        pthread_mutex_lock(&lock);
        shared_data++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Race condition tanpa mutex
    printf("Tanpa Mutex:\n");
    shared_data = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Shared data (tanpa sinkronisasi): %d\n", shared_data);

    // Menginisialisasi mutex untuk versi aman dari race condition
    pthread_mutex_init(&lock, NULL);

    // Aman dari race condition dengan mutex
    printf("\nDengan Mutex:\n");
    shared_data = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_with_lock, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Shared data (dengan sinkronisasi): %d\n", shared_data);

    // Menghancurkan mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

