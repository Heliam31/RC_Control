#include <stdio.h>

// Thread function that prints a message
void* thread_function(void* arg) {
    printf("Hello from the thread!\n");
    return NULL;
}