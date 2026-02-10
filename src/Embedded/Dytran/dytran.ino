#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
// #include <FlexCAN_T4.h>
#include <SPI.h>

#include <Adafruit_NeoPixel.h>

// bus and message definition
// FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
// // CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
// static CAN_message_t msg;
// #define CAN2_BAUDRATE 1000000

// signal definitions
// #include "CAN/raptor_CAN1.hpp"
// #include "CAN/raptor_CAN2.hpp"

// sensor definitions
#include "sensors.hpp"

// outgoing can message definitions
// #include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

//Cycle ID logic
// #include "cyclic_id.hpp"

unsigned long currentMicros;

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(1000000);

  // initialize SPI communication
  SPI.begin();

  //initialize the CAN Bus and set its baud rate to 1Mb
  // cbus2.begin();
  // cbus2.setBaudRate(CAN2_BAUDRATE);

  //initialize ADCs
  initialize_ADCs();

}

void loop() {

  currentMicros = micros(); // Get the current time in microseconds
  // Serial.println(currentMillis); // Print the time since the program started

  rainbow_pixels(GLO_neopixel);
  sample_ADCs_1();
  
  static EasyTimer sample_timer(1000); //3000 Hz
    if(sample_timer.isup()) {
      
      Serial.print(currentMicros);
      Serial.print(',');
      Serial.print(voltage_to_g(ax_raw.avg()));
      Serial.print(',');
      Serial.print(voltage_to_g(ay_raw.avg()));
      Serial.print(',');
      Serial.print(voltage_to_g(az_raw.avg()));
      Serial.print(',');
      Serial.print(voltage_to_g(gx_raw.avg()));
      Serial.print(',');
      Serial.print(voltage_to_g(gy_raw.avg()));
      Serial.print(',');
      Serial.println(voltage_to_g(gz_raw.avg()));

      // use below for zero offset calibration
      /* 
      Serial.println("ax_raw");
      Serial.println(ax_raw.avg());

      Serial.println("ay_raw");
      Serial.println(ay_raw.avg());

      Serial.println("az_raw");
      Serial.println(az_raw.avg());

      Serial.println("gx_raw");
      Serial.println(gx_raw.avg());

      Serial.println("gy_raw");
      Serial.println(gy_raw.avg());

      Serial.println("gz_raw");
      Serial.println(gz_raw.avg());
      */
      
      // Serial.println("ax_raw");
      // Serial.println(voltage_to_g(ax_raw.avg()));

      // Serial.println("gx_raw");
      // Serial.println(voltage_to_g(gx_raw.avg()));

      // Serial.println("ay_raw");
      // Serial.println(voltage_to_g(ay_raw.avg()));

      // Serial.println("gy_raw");
      // Serial.println(voltage_to_g(gy_raw.avg()));

      // Serial.println("az_raw");
      // Serial.println(voltage_to_g(az_raw.avg()));

      // Serial.println("gz_raw");
      // Serial.println(voltage_to_g(gz_raw.avg()));

      // Serial.println("test_false");
      // Serial.println(voltage_to_g(test.avg()));
    
    }
}