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
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;

#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

#define READ_RESOLUTION_BITS 12
// const int GLO_max_analog_write_pwm = 255;

#define WAKE_PIN 0

#define CHANNEL1_PIN 3
#define CHANNEL2_PIN 4
#define CHANNEL3_PIN 5
#define CHANNEL4_PIN 6
#define CHANNEL5_PIN 7
#define CHANNEL6_PIN 20
#define CHANNEL7_PIN 19
#define CHANNEL8_PIN 18

#define CHANNEL7_PWM_PIN 15
#define CHANNEL8_PWM_PIN 14

#define BRAKELIGHT_PIN 32

#define MUX0 41
#define MUX1 40
#define MUX2 39
#define MUX_EN 38

// DigiPot SPI settings (MAX5424)
#define DPOT_SPI_HZ 1000000 // 1 MHz (<= 5 MHz max for MAX5424)

// Select which DPOT/efuse channel (0..7)
void select_efuse(uint8_t ch) {
  ch &= 0x07;
  digitalWrite(MUX0, (ch >> 0) & 1);
  digitalWrite(MUX1, (ch >> 1) & 1);
  digitalWrite(MUX2, (ch >> 2) & 1);
}

// Set MAX5424 wiper position (0..255) on a given channel (0..7)
// void set_digipot_position(uint8_t channel, int pos) {
//   if (pos < 0) pos = 0;
//   if (pos > 255) pos = 255;

//   //select_efuse(channel);

//   // Enable decoder so selected CS becomes active (assumes active-low CS)
//   digitalWrite(mux_en, HIGH);
//   pinMode(3, OUTPUT);
//   digitalWrite(3, HIGH);
//   pinMode(4, OUTPUT);
//   digitalWrite(4, HIGH);
//   pinMode(5, OUTPUT);
//   digitalWrite(5, HIGH);
//   pinMode(6, OUTPUT);
//   digitalWrite(6, HIGH);
//   pinMode(7, OUTPUT);
//   digitalWrite(7, HIGH);

//   pinMode(32, OUTPUT);
//   digitalWrite(32, HIGH);

//   SPI1.beginTransaction(SPISettings(DPOT_SPI_HZ, MSBFIRST, SPI_MODE0));
//   SPI1.transfer((uint8_t)0x00);           // C1C0 = 00 -> write wiper register
//   SPI1.transfer((uint8_t)0xFA);           // D7..D0
//   SPI1.endTransaction();

//   // Disable decoder to de-assert CS
//   digitalWrite(mux_en, LOW);
// }

void digipot_setup() {

  // eFuse / DPOT mux pins
  pinMode(MUX0, OUTPUT);
  pinMode(MUX1, OUTPUT);
  pinMode(MUX2, OUTPUT);
  pinMode(MUX_EN, OUTPUT);

  digitalWrite(MUX_EN, HIGH);
  digitalWrite(MUX0, LOW);
  digitalWrite(MUX1, HIGH);
  digitalWrite(MUX2, HIGH);

  SPI1.beginTransaction(SPISettings(DPOT_SPI_HZ, MSBFIRST, SPI_MODE0));
  SPI1.transfer((uint8_t)0x00);           // C1C0 = 00 -> write wiper register
  SPI1.transfer((uint8_t)0xFA);           // D7..D0
  SPI1.endTransaction();

  digitalWrite(MUX_EN, LOW);

}

void channel_enable(){

  digitalWrite(MUX_EN, HIGH);
  pinMode(CHANNEL1_PIN, OUTPUT);
  digitalWrite(CHANNEL1_PIN, HIGH);
  pinMode(CHANNEL2_PIN, OUTPUT);
  digitalWrite(CHANNEL2_PIN, HIGH);
  pinMode(CHANNEL3_PIN, OUTPUT);
  digitalWrite(CHANNEL3_PIN, HIGH);
  pinMode(CHANNEL4_PIN, OUTPUT);
  digitalWrite(CHANNEL4_PIN, HIGH);
  pinMode(CHANNEL5_PIN, OUTPUT);
  digitalWrite(CHANNEL5_PIN, HIGH);

  // wake switch is handled in harness
  pinMode(CHANNEL6_PIN, OUTPUT);
  digitalWrite(CHANNEL6_PIN, HIGH);

  // channel 7 and channel 8 currently not functional, use as spares

  pinMode(CHANNEL7_PIN, OUTPUT);
  digitalWrite(CHANNEL7_PIN, LOW);
  pinMode(CHANNEL8_PIN, OUTPUT);
  digitalWrite(CHANNEL8_PIN, LOW);

  pinMode(BRAKELIGHT_PIN, OUTPUT);
  digitalWrite(BRAKELIGHT_PIN, HIGH);

}

// Timer Definitions
EasyTimer engine_time_update_timer(1);
EasyTimer odometer_update_timer(2);

// Sensor Sampling Definitions
#include "sensors.hpp"

// Fan & Water Pump Control
#include "fans.hpp"

// CAN Message Definitions
#include "CAN/SR26_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"
#include "can_send.hpp"

// Miscellaneous Functions
#include "misc_fcns.hpp"

// On-Board Diagnostics
// #include "obd.hpp"

// Debugging Timer
// EasyTimer debug(2);
// const bool GLO_debug = false;

// Global fan and wp Speed Signal (Controlled by CAN)
int fan_signalL = 3; // Default value
int fan_signalR = 3;
int wp_signal1 = 3;
int wp_signal2 = 3;

void setup() { //high 18 low 26
  analogReadResolution(READ_RESOLUTION_BITS);

  // Initialize serial communication
  Serial.begin(112500);

  can1.begin();
  can1.setBaudRate(500000);
  can2.begin();
  can2.setBaudRate(1000000);
  
  set_mailboxes();

  // initialize the ADC sensors
  initialize_ADCs();
  // Serial.println("ADCs Initialized");

  SPI.begin();
  SPI1.begin();
  // Serial.println("SPI Began");

  channel_enable();
  // Serial.println("Channels Enabled");

  digipot_setup();
  // Serial.println("Digipots Setup");

  // neat brakelight animation
  brakelight_start();
}

// placeholder function for undefined
void engine_timer(int hours, int minutes) {
  Serial.println("Engine timer update (placeholder function)");
}

void odometer(float speed, int mileage) {
  Serial.println("Odometer update (placeholder function)");
}

int lastCounter = VCU_counterMsg201.can_value();
float lastT = 0.0;
bool vcu_timeout = false;
bool has_received_vcu_msg = false;
float elapsed = 0;

void loop() {

  sample_ADCs();

  // if (debug.isup()){
  //   // Serial.println("Imon_pdm: ");
  //   // Serial.println(Imon_pdm.avg());

  //   Serial.println("pdm_volt_sens: ");
  //   Serial.println(pdm_volt_sens.avg());

  //   // Serial.println("brakelight_volt_sens: ");
  //   // Serial.println(brakelight_volt_sens.avg());

  //   // Serial.println("Imon_brakelight: ");
  //   // Serial.println(Imon_brakelight.avg());
    
  //   Serial.println("volt_ch6: ");
  //   Serial.println(volt_ch6.avg());

  //   Serial.println("Imon_ch6: ");
  //   Serial.println(Imon_ch6.avg());
  // }

  read_CAN();

  brakelight_run();

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
    // Serial.println("timeout");
  }

  // if (vcu_timeout == true) {
  //   Serial.println("timeout");
  // }

  fan_signalL = vcu_timeout ? 0 : VCU_radFanLDuty.can_value() / 10.0;
  fan_signalR = vcu_timeout ? 0 : VCU_radFanRDuty.can_value() / 10.0;
  wp_signal1 = vcu_timeout ? 0 : VCU_waterPumpDuty.can_value() / 10.0;
  wp_signal2 = vcu_timeout ? 0 : VCU_waterPumpDuty.can_value() / 10.0;

  updateFanSpeed(fan_signalL, fan_signalR, wp_signal1, wp_signal2);

  fan_left_override = fan_signalL;
  fan_right_override = fan_signalR;
  wp1_override = wp_signal1;
  wp2_override = wp_signal2;

  // water_pump1.set_pwm(0,0,2, 80);
  // water_pump1.set_pwm(0,0,2, 80);

  // fan_left.set_pwm(0, 0, 2, 0);
  // fan_right.set_pwm(0, 0, 2, 0);
  send_can2();
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  can1.setMaxMB(64);  // use all mailboxes of course
  can2.setMaxMB(64);

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
    can2.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_STD_MAILBOXES;
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES); i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
    can2.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
  }
  for (int i = (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES);
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES + NUM_TX_MAILBOXES);
       i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, TX, STD);
    can2.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

  // be sure to assign at least one mailbox to each message that you want to
  // read. filtering allows us to avoid using clock cycles to read messages that
  // we have no interest in. it also reserves a slot for messages as they are
  // recieved.
  can1.setMBFilter(REJECT_ALL);
  can1.setMBFilter(MB0, VCU_radFanLDuty.get_msg_id());
  can1.setMBFilter(MB1, VCU_brakeLightCmd.get_msg_id());
  can1.setMBFilter(MB2, 0);
  can1.setMBFilter(MB3, 0);
  can1.setMBFilter(MB4, 0);
  can1.setMBFilter(MB5, 0);
  can1.setMBFilter(MB6, 0);
  can1.setMBFilter(MB7, 0);
  can1.setMBFilter(MB8, 0);
  can1.setMBFilter(MB9, 0);
  can1.setMBFilter(MB10, 0);
  can1.setMBFilter(MB11, 0);
  can1.setMBFilter(MB12, 0);
  can1.setMBFilter(MB13, 0);
  can1.setMBFilter(MB14, 0);

  can2.setMBFilter(REJECT_ALL);
  can2.setMBFilter(MB0, 0);
  can2.setMBFilter(MB1, 0);
  can2.setMBFilter(MB2, 0);
  can2.setMBFilter(MB3, 0); 
  can2.setMBFilter(MB4, 0);
  can2.setMBFilter(MB5, 0);
  can2.setMBFilter(MB6, 0);
  can2.setMBFilter(MB7, 0);
  can2.setMBFilter(MB8, 0);
  can2.setMBFilter(MB9, 0);
  can2.setMBFilter(MB10, 0);
  can2.setMBFilter(MB11, 0);
  can2.setMBFilter(MB12, 0);
  can2.setMBFilter(MB13, 0);
  can2.setMBFilter(MB14, 0);
}

void read_CAN() {
  int count = 0;

  while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_SR26_CAN1(rxmsg);
    count++;
  }

  while (can2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_SR26_CAN2(rxmsg);
    count++;
  }
}