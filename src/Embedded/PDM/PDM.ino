#include <PWMControl.h>

// Dave Yonkers, 2022

#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <BoardTemp.h>
#include <EepromHelper.h>

// CAN Bus Declaration
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;

#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

// Global Variable Definitions
const int GLO_read_resolution_bits = 12;
const int GLO_max_analog_write_pwm = 255;

const int GLO_brakelight_teensy_pin = 32;
const int VCU_brakelight = 0;
//const int GLO_data_circuit_teensy_pin = 5;
const int GLO_NeoPixel_teensy_pin = 2;

// New pin definitions
const int PIN_INPUT_CTRL = 0;
const int PIN_OUTPUT_CTRL = 20;

// eFuse / DigiPot mux pins (SN74HCT138 address + enable)
const int mux0 = 41;
const int mux1 = 40;
const int mux2 = 39;
const int mux_en = 38;

// DigiPot SPI settings (MAX5424)
static const uint32_t DPOT_SPI_HZ = 1000000; // 1 MHz (<= 5 MHz max for MAX5424)

// Select which DPOT/efuse channel (0..7)
void select_efuse(uint8_t ch) {
  ch &= 0x07;
  digitalWrite(mux0, (ch >> 0) & 1);
  digitalWrite(mux1, (ch >> 1) & 1);
  digitalWrite(mux2, (ch >> 2) & 1);
}

// Set MAX5424 wiper position (0..255) on a given channel (0..7)
void set_digipot_position(uint8_t channel, int pos) {
  if (pos < 0) pos = 0;
  if (pos > 255) pos = 255;

  //select_efuse(channel);

  // Enable decoder so selected CS becomes active (assumes active-low CS)
  digitalWrite(mux_en, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);

  Serial.println("run");

  SPI1.beginTransaction(SPISettings(DPOT_SPI_HZ, MSBFIRST, SPI_MODE0));
  SPI1.transfer((uint8_t)0x00);           // C1C0 = 00 -> write wiper register
  SPI1.transfer((uint8_t)0xFA);           // D7..D0
  SPI1.endTransaction();

  Serial.println("run2");

  // Disable decoder to de-assert CS
  digitalWrite(mux_en, LOW);
}

int GLO_NeoPixel_brightness_percent = 10;
Adafruit_NeoPixel GLO_obd_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

BoardTempDiode board_temp(21, GLO_read_resolution_bits, 28.1, 594);
EasyTimer board_temp_sample_timer(50);

/*
// EEPROM
const int eeprom_cs_pin = 9;
EEPROM_25LC128 eeprom(eeprom_cs_pin);
*/

// Timer Definitions
EasyTimer engine_time_update_timer(1);
EasyTimer odometer_update_timer(2);

// EEPROM Signals
#include "EEPROM_sigs.hpp"

// Sensor Sampling Definitions
#include "sensors.hpp"

// Fan & Water Pump Control
#include "fans.hpp"

// CAN Message Definitions
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"
#include "can_send.hpp"

// Miscellaneous Functions
#include "misc_fcns.hpp"

// On-Board Diagnostics
#include "obd.hpp"

// Debugging Timer
EasyTimer debug(2);
const bool GLO_debug = false;

// Global fan and wp Speed Signal (Controlled by CAN)
int fan_signalL = 3; // Default value
int fan_signalR = 3;
int wp_signal1 = 3;
int wp_signal2 = 3;

void setup() { //high 18 low 26
  analogReadResolution(GLO_read_resolution_bits);

  // pin 0 input, pin 20 output
  pinMode(PIN_INPUT_CTRL, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_CTRL, OUTPUT);
  digitalWrite(PIN_OUTPUT_CTRL, LOW);

  // eFuse / DPOT mux pins
  pinMode(mux0, OUTPUT);
  pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux_en, OUTPUT);

  digitalWrite(mux_en, HIGH);
  digitalWrite(mux0, LOW);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);

  // begin OBD Neopixel
  GLO_obd_neopixel.begin();
  GLO_obd_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_obd_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_obd_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);

  //initialize the CAN Bus and set its baud rate to 1Mb
  can1.begin();
  // can1.setBaudRate(1000000);
  can1.setBaudRate(500000);
  can2.begin();
  can2.setBaudRate(1000000);
  set_mailboxes();

  // initialize the ADC sensors
  initialize_ADCs();

  // initialize SPI communication
  Serial.println("before spi begin");

  SPI1.setSCK(27);
  pinMode(26, OUTPUT);
  SPI1.setMOSI(26);
  SPI1.begin();

  Serial.println("after spi begin");

  // initialize brakelight pin
  pinMode(GLO_brakelight_teensy_pin, OUTPUT);

  GLO_obd_neopixel.setPixelColor(0, 0, 255, 0); // green
  GLO_obd_neopixel.show();

  // board temp initialization
  board_temp.begin();

  // neat brakelight animation
  //brakelight_start();

  set_digipot_position(4, 254);
}

// placeholder function for undefined
void engine_timer(int hours, int minutes) {
  Serial.println("Engine timer update (placeholder function)");
}

void odometer(float speed, int mileage) {
  Serial.println("Odometer update (placeholder function)");
}

const bool testMode = true;
const int testNum = 1;

int lastCounter = VCU_counterMsg201.can_value();
float lastT = 0.0;
bool vcu_timeout = false;
bool has_received_vcu_msg = false;
float elapsed = 0;

void loop() {
  // pin 0 controls pin 20
  // with INPUT_PULLUP:
  // pin 20 goes HIGH when pin 0 is pulled LOW
  if (digitalRead(PIN_INPUT_CTRL) == LOW) {
    digitalWrite(PIN_OUTPUT_CTRL, HIGH);
  } else {
    digitalWrite(PIN_OUTPUT_CTRL, LOW);
  }

  //sample_ADCs();
  if (board_temp_sample_timer.isup()) board_temp.sample();
  read_CAN();

/*
  Serial.print("brakelight volt sens: ");
  Serial.println(brakelight_volt_sens.avg());
  Serial.print("pdm curr sens: ");
  Serial.println(Imon_pdm.avg());
  Serial.print("volt ch1 sens: ");
  Serial.println(volt_ch1.avg());
  Serial.println("");
*/

  static EasyTimer efuse_on_off(1);

  static bool efuse_on = true;

  /*
  if (efuse_on_off.isup()) {
    if (efuse_on) {
      digitalWrite(7, LOW);
      Serial.println("LOW");
      efuse_on = false;
    } else {
      digitalWrite(7, HIGH);
      Serial.println("HIGH");
      efuse_on = true;
    }

  }
  */

  elapsed = (millis() - lastT);
  if (has_received_vcu_msg == false) {
    elapsed = 0;
  }
  if (VCU_counterMsg201.can_value() != lastCounter) {
    lastT = millis();
    lastCounter = VCU_counterMsg201.can_value();
    has_received_vcu_msg = true;
  }

  if (elapsed > 300 && has_received_vcu_msg == true) {
    vcu_timeout = true;
    Serial.println("timeout");
  }

  if (vcu_timeout == true) {
    Serial.println("timeout");
  }

  if (testMode) {
    if (testNum == 1) {
      //Serial.println(PDM_fanRightDutyCycle.can_value());
      PDM_fanRightDutyCycle.set_can_value(100);
      fan_signalL = PDM_fanRightDutyCycle.can_value();
      send_can2();
    } else if (testNum == 2) {
      fan_signalL = vcu_timeout ? 0 : VCU_radFanLDuty.can_value() / 10.0;
      fan_signalR = vcu_timeout ? 0 : VCU_radFanRDuty.can_value() / 10.0;
      wp_signal1   = vcu_timeout ? 0 : VCU_waterPumpDuty.can_value() / 10.0;
      wp_signal2   = vcu_timeout ? 0 : VCU_waterPumpDuty.can_value() / 10.0;
      send_can2();
    }
  } else {
    send_can2();
  }

  updateFanSpeed(fan_signalL, fan_signalR, wp_signal1, wp_signal2);

  fan_left_override = fan_signalL;
  fan_right_override = fan_signalR;
  wp1_override = wp_signal1;
  wp2_override = wp_signal2;

  fan_left.set_pwm(2);
  fan_right.set_pwm(2);
}

void set_mailboxes() {
  can2.setMaxMB(64);
  can2.enableFIFO();
  can2.setMB(MB4, RX, STD);
  can2.setMB(MB5, RX, STD);
  can2.setMB(MB6, RX, STD);
  can2.setMB(MB7, RX, STD);
  can2.setMB(MB8, RX, STD);
  can2.setMB(MB9, RX, STD);
  can2.setMB(MB10, RX, STD);
  can2.setMB(MB11, RX, STD);
  can2.setMB(MB12, RX, EXT);
  can2.setMB(MB13, RX, EXT);
  can2.setMB(MB14, RX, EXT);
  can2.setMB(MB15, RX, EXT);
}

void read_CAN() {
  int count = 0;

  while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN1(rxmsg);
    count++;
  }

  while (can2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN2(rxmsg);
    count++;
  }
}