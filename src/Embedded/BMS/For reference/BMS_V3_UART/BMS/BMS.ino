#include <Arduino.h>
#include "config.h"
#include "bq_comm.h"

void setup() {
    Serial.begin(9600);
    unsigned long startup_wait = millis();
    while (!Serial && (millis() - startup_wait < 5000)); 
    BMS_DEBUG_PRINTLN("\n\nBMS Controller Starting...");

    //bqInitCommunication();
    bqAutoAddressStack();

    BQ_UART_SERIAL.begin(BQ_UART_BAUDRATE, SERIAL_8N1);
    BQ_UART_SERIAL.setTimeout(SERIAL_TIMEOUT_MS);

    BMS_DEBUG_PRINTLN("Setup Complete. Starting FSM.");
}

int i = 0;

void loop() {
    if(i < 100){
        i++;
    }else{
        i = i-99;
    }
}