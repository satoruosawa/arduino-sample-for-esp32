#include <Arduino.h>
#include <BLEDevice.h>

#define SERVICE_UUID "e77fe789-2d78-4123-be83-166486bb8b55"
#define CHARACTERISTIC_UUID "ea1fb90b-6411-40e6-abca-e9b1b82350fa"

BLEServer * SERVER;
BLEService * SERVICE;
BLECharacteristic * CHARACTERISTIC;

void setup() {
  BLEDevice::init("ESP32_TEST");

  SERVER = BLEDevice::createServer();
  SERVICE = SERVER->createService(SERVICE_UUID);
  CHARACTERISTIC = SERVICE->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );

  SERVICE->start();
  SERVER->startAdvertising();

  CHARACTERISTIC->setValue("Write");
}

void loop() {
}
