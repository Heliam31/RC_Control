#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void msleep(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

#include "simpleble_c/simpleble.h"

#define PERIPHERAL_LIST_SIZE (size_t)10
#define SERVICES_LIST_SIZE (size_t)32

typedef struct {
    simpleble_uuid_t service;
    simpleble_uuid_t characteristic;
} service_characteristic_t;

static void clean_on_exit(void);

static void adapter_on_scan_start(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_stop(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata);
static void peripheral_on_notify(simpleble_peripheral_t handle, simpleble_uuid_t service,
                                 simpleble_uuid_t characteristic, const uint8_t* data, size_t data_length,
                                 void* userdata);

static service_characteristic_t characteristic_list[SERVICES_LIST_SIZE] = {0};
static simpleble_peripheral_t peripheral_list[PERIPHERAL_LIST_SIZE] = {0};
static size_t peripheral_list_len = 0;
static simpleble_adapter_t adapter = NULL;

int main() {
    simpleble_err_t err_code = SIMPLEBLE_SUCCESS;
    atexit(clean_on_exit);

    // NOTE: It's necessary to call this function before any other to allow the
    // underlying driver to run its initialization routine.
    size_t adapter_count = simpleble_adapter_get_count();
    if (adapter_count == 0) {
        printf("No adapter was found.\n");
        return 1;
    }

    // TODO: Allow the user to pick an adapter.
    adapter = simpleble_adapter_get_handle(0);
    if (adapter == NULL) {
        printf("No adapter was found.\n");
        return 1;
    }

    simpleble_adapter_set_callback_on_scan_start(adapter, adapter_on_scan_start, NULL);
    simpleble_adapter_set_callback_on_scan_stop(adapter, adapter_on_scan_stop, NULL);
    simpleble_adapter_set_callback_on_scan_found(adapter, adapter_on_scan_found, NULL);

    simpleble_adapter_scan_for(adapter, 5000);

    printf("The following devices were found:\n");
    for (size_t i = 0; i < peripheral_list_len; i++) {
        simpleble_peripheral_t peripheral = peripheral_list[i];
        char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
        char* peripheral_address = simpleble_peripheral_address(peripheral);
        printf("[%zu] %s [%s]\n", i, peripheral_identifier, peripheral_address);
        simpleble_free(peripheral_identifier);
        simpleble_free(peripheral_address);
    }

    int selection = -1;
    printf("Please select a device to connect to: ");
    scanf("%d", &selection);

    if (selection < 0 || selection >= (int)peripheral_list_len) {
        printf("Invalid selection.\n");
        return 1;
    }

    simpleble_peripheral_t peripheral = peripheral_list[selection];

    char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char* peripheral_address = simpleble_peripheral_address(peripheral);
    printf("Connecting to %s [%s]\n", peripheral_identifier, peripheral_address);
    simpleble_free(peripheral_identifier);
    simpleble_free(peripheral_address);

    err_code = simpleble_peripheral_connect(peripheral);
    if (err_code != SIMPLEBLE_SUCCESS) {
        printf("Failed to connect.\n");
        return 1;
    }

    printf("Successfully connected, listing services and characteristics.\n");

    size_t characteristic_count = 0;
    for (size_t i = 0; i < simpleble_peripheral_services_count(peripheral); i++) {
        simpleble_service_t service;
        err_code = simpleble_peripheral_services_get(peripheral, i, &service);

        if (err_code != SIMPLEBLE_SUCCESS) {
            printf("Failed to get service.\n");
            return 1;
        }

        for (size_t j = 0; j < service.characteristic_count; j++) {
            if (characteristic_count >= SERVICES_LIST_SIZE) {
                break;
            }

            printf("[%zu] %s %s\n", characteristic_count, service.uuid.value, service.characteristics[j].uuid.value);
            characteristic_list[characteristic_count].service = service.uuid;
            characteristic_list[characteristic_count].characteristic = service.characteristics[j].uuid;
            characteristic_count++;
        }
    }

    selection = -1;
    printf("Please select a characteristic to read from: ");
    scanf("%d", &selection);

    if (selection < 0 || selection >= (int)characteristic_count) {
        printf("Invalid selection.\n");
        return 1;
    }

    simpleble_peripheral_notify(peripheral, characteristic_list[selection].service,
                                characteristic_list[selection].characteristic, peripheral_on_notify, NULL);

    // Sleep for 5 seconds
    msleep(5000);

    simpleble_peripheral_unsubscribe(peripheral, characteristic_list[selection].service,
                                     characteristic_list[selection].characteristic);

    simpleble_peripheral_disconnect(peripheral);

    return 0;
}

static void clean_on_exit(void) {
    printf("Releasing allocated resources.\n");

    // Release all saved peripherals
    for (size_t i = 0; i < peripheral_list_len; i++) {
        simpleble_peripheral_release_handle(peripheral_list[i]);
    }

    // Let's not forget to release the associated handle.
    simpleble_adapter_release_handle(adapter);
}

static void adapter_on_scan_start(simpleble_adapter_t adapter, void* userdata) {
    char* identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL) {
        return;
    }

    printf("Adapter %s started scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

static void adapter_on_scan_stop(simpleble_adapter_t adapter, void* userdata) {
    char* identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL) {
        return;
    }

    printf("Adapter %s stopped scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata) {
    char* adapter_identifier = simpleble_adapter_identifier(adapter);
    char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char* peripheral_address = simpleble_peripheral_address(peripheral);

    if (adapter_identifier == NULL || peripheral_identifier == NULL || peripheral_address == NULL) {
        return;
    }

    printf("Adapter %s found device: %s [%s]\n", adapter_identifier, peripheral_identifier, peripheral_address);

    if (peripheral_list_len < PERIPHERAL_LIST_SIZE) {
        // Save the peripheral
        peripheral_list[peripheral_list_len++] = peripheral;
    } else {
        // As there was no space left for this peripheral, release the associated handle.
        simpleble_peripheral_release_handle(peripheral);
    }

    // Let's not forget to release all allocated memory.
    simpleble_free(peripheral_identifier);
    simpleble_free(peripheral_address);
}

static void peripheral_on_notify(simpleble_peripheral_t handle, simpleble_uuid_t service,
                                 simpleble_uuid_t characteristic, const uint8_t* data, size_t data_length,
                                 void* userdata) {
    printf("Received: ");
    for (size_t i = 0; i < data_length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
