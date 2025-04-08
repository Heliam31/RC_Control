#ifndef THROTTLEINPUT_H
#define THROTTLEINPUT_H

#include <pthread.h>

extern int running;
extern int throttle_position;
extern pthread_mutex_t throttle_mutex;


void* hotas_inputs(void* arg);

#endif