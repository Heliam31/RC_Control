#include <stdio.h>
#include <pthread.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void* thread_function(void* arg);

int main() {
    pthread_t thread_id;

    // Create a new thread that will run the thread_function
    if (pthread_create(&thread_id, NULL, thread_function, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }



    // Wait for the thread to finish
    if (pthread_join(thread_id, NULL) != 0) {
        perror("Thread join failed");
        return 1;
    }

    printf("Main thread finished\n");
    return 0;
}