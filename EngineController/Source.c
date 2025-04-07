#include <stdio.h>
#include <pthread.h>

int thread_function(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread en cours d'exécution\n");
    }
    return 0;
}


int main(void) {
    thrd_t JoyInput;
    if (thrd_create(&JoyInput, thread_function, NULL) != thrd_success) {
        fprintf(stderr, "Erreur lors de la création du thread\n");
        return 1;
    }

    printf("Thread principal\n");
    thrd_join(JoyInput, NULL);
    return 0;
}