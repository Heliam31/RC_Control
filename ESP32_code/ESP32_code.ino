#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

BLECharacteristic* pCharacteristic;
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "0000fff1-0000-1000-8000-00805f9b34fb" 

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_Control");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

  pCharacteristic->setValue("4");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
/*  String rxValue = pCharacteristic->getValue();

  if (rxValue.length() > 0) {
    int throttle = rxValue.toInt();  // conversion chaîne → int
    Serial.printf("Throttle reçu : %d %%\n", throttle);
    pCharacteristic->setValue(""); // Clear pour éviter de le relire en boucle
  }*/

  delay(200);
}