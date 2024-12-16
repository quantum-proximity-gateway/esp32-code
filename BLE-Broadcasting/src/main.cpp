#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID "2246ef74-f912-417f-8530-4a7df291d584"
#define CHARACTERISTIC_UUID "a3445e11-5bff-4d2a-a3b1-b127f9567bb6"

class MyServer : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("Connected.");
    }

    void onDisconnect(BLEServer* pServer) {
        Serial.println("Disconnected.");
        pServer->getAdvertising()->start(); // Fixes bug where disconnecting stops advertising
    }
};


void setup() {
    Serial.begin(9600);
    Serial.println("Starting BLE Server");
    BLEDevice::init("ESP32 Key"); // Change this to whatever you need
    // BLEAddress address = BLEDevice::getAddress();
    // Serial.print("Device MAC Address: ");
    // Serial.println(address.toString().c_str());
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServer());
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE
    );
    
    pCharacteristic->setValue("{Key: 123554432432, MAC: 2a:23}");
    pService->start();

    BLEAdvertisementData oAdvertisementData;
    oAdvertisementData.setName("ESP32 Key");  // Explicitly set the name
    oAdvertisementData.setCompleteServices(BLEUUID(SERVICE_UUID));  // Add service UUID
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->setScanResponse(false);  // Disable scan response if not needed
    pAdvertising->start();
    BLEDevice::startAdvertising();
}

void loop() {
}