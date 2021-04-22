#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> //Library to use BLE as server
#include "../header.hpp"

#define SERVICE_UUID s_UUID
#define CHARACTERISTIC_UUID c_UUID

void InitBLE(){
  // Create BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setValue("Im learning BLE!!");
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined!");

}

void setup() {
  Serial.begin(9600);
  Serial.print("Starting Magnetic Sensor v0.1..");
  BLEDevice::init("Mag Sensor 1");
  InitBLE();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}