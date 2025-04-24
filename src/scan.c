#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simpleble_c/simpleble.h"

#include "throttleinput.h"
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#define PERIPHERAL_LIST_SIZE (size_t)10

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "0000fff1-0000-1000-8000-00805f9b34fb" 

extern int running;
extern int throttle_position;
extern pthread_mutex_t throttle_mutex;

static void clean_on_exit(void);

static void adapter_on_scan_start(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_stop(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata);
static void peripheral_on_notify(simpleble_peripheral_t handle, simpleble_uuid_t service,simpleble_uuid_t characteristic, const uint8_t* data, size_t data_length,void* userdata);


static simpleble_peripheral_t peripheral_list[PERIPHERAL_LIST_SIZE] = {0};
static size_t peripheral_list_len = 0;
static simpleble_adapter_t adapter = NULL;

static char* ESP_addr = "1C:69:20:A4:C6:1E";

static int service_nb = -1;
static int charac_nb = -1;

//-------------------------------------------------------------------------------------------------------------------//
//                                                                                                                   //
//                                                     MAIN                                                          //
//                                                                                                                   //
//-------------------------------------------------------------------------------------------------------------------//
void* ble_sender(void* arg) {
    simpleble_err_t err_code = SIMPLEBLE_SUCCESS;
    atexit(clean_on_exit);

    // NOTE: It's necessary to call this function before any other to allow the
    // underlying driver to run its initialization routine.
    size_t adapter_count = simpleble_adapter_get_count();
    if (adapter_count == 0) {
        printf("No adapter was found.\n");
        return NULL;
    }

    // TODO: Allow the user to pick an adapter.
    adapter = simpleble_adapter_get_handle(0);
    if (adapter == NULL) {
        printf("No adapter was found.\n");
        return NULL;
    }

    simpleble_adapter_set_callback_on_scan_start(adapter, adapter_on_scan_start, NULL);
    simpleble_adapter_set_callback_on_scan_stop(adapter, adapter_on_scan_stop, NULL);
    simpleble_adapter_set_callback_on_scan_found(adapter, adapter_on_scan_found, NULL);

    simpleble_adapter_scan_for(adapter, 5000);

    int selection = -1;
    printf("The following devices were found:\n");
    for (size_t i = 0; i < peripheral_list_len; i++) {
        simpleble_peripheral_t peripheral = peripheral_list[i];
        char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
        char* peripheral_address = simpleble_peripheral_address(peripheral);
        

        if (strcmp(peripheral_identifier, "ESP32_Control") == 0) {
            selection = i;
            printf("TROUVE L'ESP32 \n");
        } else {
            printf("[%zu] %s [%s]\n", i, peripheral_identifier, peripheral_address);
        }
        
        simpleble_free(peripheral_identifier);
        simpleble_free(peripheral_address);
    }

/*
    int selection = -1;
    printf("Please select a device to connect to: ");
    scanf("%d", &selection);

    if (selection < 0 || selection >= (int)peripheral_list_len) {
        printf("Invalid selection.\n");
        return 1;
    }
*/

    simpleble_peripheral_t peripheral = peripheral_list[selection];

    char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char* peripheral_address = simpleble_peripheral_address(peripheral);
    printf("Connecting to %s [%s]\n", peripheral_identifier, peripheral_address);
    simpleble_free(peripheral_identifier);
    simpleble_free(peripheral_address);

    err_code = simpleble_peripheral_connect(peripheral);
    if (err_code != SIMPLEBLE_SUCCESS) {
        printf("Failed to connect.\n");
        return NULL;
    }

    size_t services_count = simpleble_peripheral_services_count(peripheral);
    printf("Successfully connected, listing %zu services.\n", services_count);

    for (size_t i = 0; i < services_count; i++) {
        simpleble_service_t service;
        err_code = simpleble_peripheral_services_get(peripheral, i, &service);

        if (err_code != SIMPLEBLE_SUCCESS) {
            printf("Failed to get service.\n");
            return NULL;
        }

        if (strcmp(SERVICE_UUID, service.uuid.value) == 0) {
            service_nb = i;
            printf("TROUVE le bon service \n");


            for (size_t j = 0; j < service.characteristic_count; j++) {

                if (strcmp(CHARACTERISTIC_UUID, service.characteristics[j].uuid.value) == 0) {
                    charac_nb = j;

                    uint8_t** data = NULL;
                    size_t* data_length = 0;
        
                    simpleble_err_t err = simpleble_peripheral_read(peripheral, service.uuid, service.characteristics[charac_nb].uuid, data, data_length);
                   
                    if (err != SIMPLEBLE_SUCCESS) {
                        printf("Erreur de lecture: %d\n", err);
                        return NULL;
                    }
        
                    // Affichage
                    printf("Valeur lue (%zu octets) : ", *data_length);
                    for (size_t i = 0; i < *data_length; i++) {
                        printf("%02X ", *data[i]);
                    }
                    printf("\n");
        
                    simpleble_free(data);
                }
    
                printf("  Characteristic: %s - (%zu descriptors)\n", service.characteristics[j].uuid.value,
                       service.characteristics[j].descriptor_count);
                for (size_t k = 0; k < service.characteristics[j].descriptor_count; k++) {
                    printf("    Descriptor: %s\n", service.characteristics[j].descriptors[k].uuid.value);
                }
            }

        }

        printf("Service: %s - (%zu characteristics)\n", service.uuid.value, service.characteristic_count);
        for (size_t j = 0; j < service.characteristic_count; j++) {

            if (strcmp(CHARACTERISTIC_UUID, service.characteristics[j].uuid.value) == 0) {
                charac_nb = j;
                printf("TROUVE le bon charac \n");
            }

            printf("  Characteristic: %s - (%zu descriptors)\n", service.characteristics[j].uuid.value,
                   service.characteristics[j].descriptor_count);
            for (size_t k = 0; k < service.characteristics[j].descriptor_count; k++) {
                printf("    Descriptor: %s\n", service.characteristics[j].descriptors[k].uuid.value);
            }
        }
    }

    int current = throttle_position;
    while(running){
        //ENVOI SI VALEUR DANS THROTTLE
        if(throttle_position != current){
            printf("[THREAD_BLE] : Valeur throttle changée à %d%%! ", throttle_position);
            current = throttle_position; 
    /*
            printf("lecture de la charac %d dans le service %d", charac_nb, service_nb);
            simpleble_service_t service;
            err_code = simpleble_peripheral_services_get(peripheral, service_nb, &service);

            uint8_t** data = NULL;
            size_t* data_length = 0;

            simpleble_err_t err = simpleble_peripheral_read(peripheral, service.uuid, service.characteristics[charac_nb].uuid, data, data_length);
                
            if (err != SIMPLEBLE_SUCCESS) {
                printf("Erreur de lecture: %d\n", err);
                return NULL;
            }

            // Affichage
            printf("Valeur lue (%zu octets) : ", *data_length);
            for (size_t i = 0; i < *data_length; i++) {
                printf("%02X ", *data[i]);
            }
            printf("\n");

            simpleble_free(data);
    */
        }

    }


    simpleble_peripheral_disconnect(peripheral);

    return NULL;
}

//-------------------------------------------------------------------------------------------------------------------//
//                                                                                                                   //
//                                                     FUNCTIONS                                                     //
//                                                                                                                   //
//-------------------------------------------------------------------------------------------------------------------//

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

    // Affichage
    printf("Valeur lue (%zu octets) : ", data_length);
    for (size_t i = 0; i < data_length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}