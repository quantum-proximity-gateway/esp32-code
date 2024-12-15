#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "2246ef74-f912-417f-8530-4a7df291d584"
#define CHARACTERISTIC_UUID "a3445e11-5bff-4d2a-a3b1-b127f9567bb6"

void setup() {
    Serial.begin(9600);
    Serial.println("Starting BLE Server");
    
    BLEDevice::init("MarwanESP32"); // Change this to whatever you need
    BLEAddress address = BLEDevice::getAddress();
    Serial.print("Device MAC Address: ");
    Serial.println(address.toString().c_str());
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE
    );
    
    pCharacteristic->setValue("HELLO WORLD");
    pService->start();

    BLEAdvertisementData oAdvertisementData;
    oAdvertisementData.setName("Marwan's ESP32 Key");  // Explicitly set the name
    oAdvertisementData.setCompleteServices(BLEUUID(SERVICE_UUID));  // Add service UUID
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->setScanResponse(false);  // Disable scan response if not needed
    pAdvertising->start();
    BLEDevice::startAdvertising();
}

void loop() {
    delay(1000);
}