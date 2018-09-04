#include <Arduino.h>
#include <BLEDevice.h>
#include <BLE2902.h>

BLEServer * SERVER;
BLEService * SERVICE;
BLECharacteristic * CHARACTERISTIC;

#define SERVICE_UUID "e77fe789-2d78-4123-be83-166486bb8b55"
#define CHARACTERISTIC_UUID "ea1fb90b-6411-40e6-abca-e9b1b82350fa"

bool DEVICE_CONNECTED = false;
uint8_t COUNT = 0;

class ServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    DEVICE_CONNECTED = true;
  };
  void onDisconnect(BLEServer* pServer) {
    DEVICE_CONNECTED = false;
  }
};

void setup() {
  BLEDevice::init("ESP32_TEST");

  SERVER = BLEDevice::createServer();
  SERVICE = SERVER->createService(SERVICE_UUID);
  CHARACTERISTIC = SERVICE->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  CHARACTERISTIC->addDescriptor(new BLE2902());

  SERVICE->start();
  SERVER->startAdvertising();

  CHARACTERISTIC->setValue("Notify");
}

void loop() {
  CHARACTERISTIC->setValue(&COUNT, 1);
  CHARACTERISTIC->notify();
  COUNT++;
  delay(1000);
}
