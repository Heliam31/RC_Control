#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "throttleinput.h"

// ESP32 mac addr = 1c:69:20:a4:c6:1c


int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, hotas_inputs, NULL);
    int current = throttle_position;
    while (running) {
        pthread_mutex_lock(&throttle_mutex);
        if(throttle_position != current){
            current = throttle_position;
            printf("Throttle: %d%%\n", current);
        }
        
        pthread_mutex_unlock(&throttle_mutex);

        
        usleep(1000); // 100ms = 100000
    }

    return 0;
}

