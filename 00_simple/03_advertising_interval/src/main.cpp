#include <Arduino.h>
#include <BLEDevice.h>

BLEServer * SERVER;
BLEService * SERVICE;
BLECharacteristic * CHARACTERISTIC;

#define SERVICE_UUID "e77fe789-2d78-4123-be83-166486bb8b55"
#define CHARACTERISTIC_UUID "ea1fb90b-6411-40e6-abca-e9b1b82350fa"

uint8_t COUNT = 0;

void setup() {
  BLEDevice::init("ESP32_TEST");

  SERVER = BLEDevice::createServer();
  SERVICE = SERVER->createService(SERVICE_UUID);
  CHARACTERISTIC = SERVICE->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ
  );

  SERVICE->start();

  // Minimum advertising interval for
  // undirected and low duty cycle directed advertising.
  // Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
  // Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec
  // 2.56sec = 4096(0x1000) * 0.625msec
  SERVER->getAdvertising()->setMinInterval(0x1000);

  // Maximum advertising interval for
  // undirected and low duty cycle directed advertising.
  // Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
  // Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec Advertising max interval
  // 5.12sec = 8192(0x2000) * 0.625msec
  SERVER->getAdvertising()->setMaxInterval(0x2000);

  // Why you have to set Min and Max?
  // https://community.cypress.com/thread/33695?start=0&tstart=0

  SERVER->startAdvertising();

  CHARACTERISTIC->setValue("Read");
}

void loop() {
}
