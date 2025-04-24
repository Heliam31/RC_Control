#include "throttleinput.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <linux/joystick.h>

int throttle_position = 0;
pthread_mutex_t throttle_mutex = PTHREAD_MUTEX_INITIALIZER;
int running = 1;

int convert_to_percent(int raw) {
    return (raw==32767)?0:(raw - 32767) * 100.0f / (2 * -32767);
}

void* hotas_inputs(void* arg) {
    const char *device = "/dev/input/js0";
    int js = open(device, O_RDONLY);
    if (js < 0) {
        perror("Could not open joystick");
        return NULL;
    }

    struct js_event e;

    printf("Reading joystick inputs (press Ctrl+C to quit):\n");
    while (running) {
        if (read(js, &e, sizeof(e)) != sizeof(e)) {
            perror("Read error");
            break;
        }


        if (e.type == JS_EVENT_AXIS) {
            if(e.number == 2){
                int percent = convert_to_percent(e.value);

                pthread_mutex_lock(&throttle_mutex);
                //printf("throttle value =%f\n", percent);
                throttle_position = percent;
                pthread_mutex_unlock(&throttle_mutex);
            }
            else{
                printf("Axis %u = %d\n", e.number, e.value);
            }
        } else if (e.type == JS_EVENT_BUTTON) {
            if (e.number == 0 && e.value == 1){
                printf("Button %u = %s\n", e.number, e.value ? "pressed" : "released");
                printf("Bye Bye");
                running = 0;
            }
            else{
                printf("Button %u = %s\n", e.number, e.value ? "pressed" : "released");
            }
        }
    }

    close(js);
    return NULL;
}