#include <Arduino.h>
#include <Wire.h>
// Define SENSOR_PIN based on which platform we're building for
#ifdef ARDUINO_AVR_UNO
    #define SENSOR_PIN PIN_A0
#endif

#ifdef ARDUINO_ESP8266_NODEMCU
    #define SENSOR_PIN 2
#endif

#ifdef ARDUINO_AVR_NANO
    #define SENSOR_PIN A0
#endif

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;

void receiveData(int byteCount);
void sendData();
int readSensor();

void setup() {
    // Setup the analog pin connected to the sensor for input
    pinMode(SENSOR_PIN, INPUT);
    pinMode(13, OUTPUT);
    Serial.begin(9600); // start serial for output
// initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

// define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);

    Serial.println("Ready!");
}

void loop() {
}

// callback for received data
void receiveData(int byteCount) {

    while(Wire.available()) {
        number = Wire.read();
        Serial.print("data received: ");
        Serial.print(byteCount);
        Serial.print( " bytes. Value: ");
        Serial.println(number);

        if (number == 1){

            if (state == 0){
                digitalWrite(13, HIGH); // set the LED on
                state = 1;
            }
            else{
                digitalWrite(13, LOW); // set the LED off
                state = 0;
            }
        }
    }
}

// callback for sending data
void sendData(){
    int number = readSensor();
    Serial.print("Sending ");
    Serial.println(number);
    Wire.write(number);
}

int readSensor(){
    return analogRead(SENSOR_PIN);
}

