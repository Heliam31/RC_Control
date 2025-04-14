#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

#define THROTTLE_HANDLE 0x0012 // Le handle de la caractéristique throttle
#define ATT_CID 4             // Le canal ATT utilisé (ATT Channel Identifier)

int main() {
    const char *ble_addr = "1C:69:20:A4:C6:1E"; // L'adresse Bluetooth de l'ESP32
    int throttle_value = 50;                    // La valeur du throttle (0 à 100)

    if (throttle_value < 0 || throttle_value > 100) {
        fprintf(stderr, "La valeur du throttle doit être comprise entre 0 et 100\n");
        return 1;
    }

    // Créer un socket Bluetooth
    int sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    if (sock < 0) {
        perror("Erreur lors de la création du socket");
        return 1;
    }

    // Configurer l'adresse du périphérique Bluetooth (ESP32)
    struct sockaddr_l2 addr = { 0 };
    addr.l2_family = AF_BLUETOOTH;
    addr.l2_psm = htobs(ATT_CID);            // Canal ATT (4)
    str2ba(ble_addr, &addr.l2_bdaddr);       // Adresse Bluetooth du périphérique

    // Connecter le client (PC) au serveur (ESP32)
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Erreur lors de la connexion");
        close(sock);
        return 1;
    }

    // Compose le message de requête d'écriture GATT
    uint8_t buffer[5];
    buffer[0] = 0x12;  // ATT_OP_WRITE_REQ (Opcode de la requête d'écriture)
    buffer[1] = THROTTLE_HANDLE & 0xff;       // Handle de la caractéristique throttle (bas)
    buffer[2] = THROTTLE_HANDLE >> 8;        // Handle de la caractéristique throttle (haut)
    buffer[3] = (uint8_t)throttle_value;     // La valeur à écrire (throttle)

    // Envoi de la requête d'écriture
    int len = 4; // 1 octet pour l'opcode + 2 octets pour le handle + 1 octet pour la valeur
    if (write(sock, buffer, len) < 0) {
        perror("Erreur lors de l'écriture");
        close(sock);
        return 1;
    }

    printf("Throttling envoyé : %d %% à l'ESP32\n", throttle_value);

    // Fermer le socket
    close(sock);
    return 0;
}