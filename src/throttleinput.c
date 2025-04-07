// hotas_throttle.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

int main() {
    const char *device = "/dev/input/js0";
    int js = open(device, O_RDONLY);
    if (js < 0) {
        perror("Could not open joystick");
        return 1;
    }

    struct js_event e;

    printf("Reading joystick inputs (press Ctrl+C to quit):\n");
    while (1) {
        if (read(js, &e, sizeof(e)) != sizeof(e)) {
            perror("Read error");
            break;
        }

        if (e.type == JS_EVENT_AXIS) {
            printf("Axis %u = %d\n", e.number, e.value);
        } else if (e.type == JS_EVENT_BUTTON) {
            printf("Button %u = %s\n", e.number, e.value ? "pressed" : "released");
        }
    }

    close(js);
    return 0;
}