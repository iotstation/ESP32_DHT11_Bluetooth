#include "BluetoothSerial.h"
#include "DHT.h"

#define DHTPIN 4          // GPIO pin where DHT11 is connected
#define DHTTYPE DHT11     // DHT 11 sensor

BluetoothSerial SerialBT; // Create a Bluetooth Serial object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);       // Start serial monitor
    SerialBT.begin("ESP32_test"); // Bluetooth name
    dht.begin();
    Serial.println("Bluetooth Started! Waiting for connections...");
}

void loop() {
    float temp = dht.readTemperature();  // Read temperature (Celsius)
    float hum = dht.readHumidity();      // Read humidity (%)

    if (isnan(temp) || isnan(hum)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Format the message as "temp:humidity"
    String data = String((int)temp) + ":" + String((int)hum);
    SerialBT.println(data);  // Send data via Bluetooth
    Serial.println("Sent: " + data);  // Debug print

    delay(1000); // Wait 1 second before next reading
}


//esp32 by Espressif Systems
