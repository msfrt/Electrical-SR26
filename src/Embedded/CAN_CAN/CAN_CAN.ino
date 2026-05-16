#ifndef CAN_CAN
#define CAN_CAN

#include <Adafruit_NeoPixel.h>
#include <BoardTemp.h>
#include <EasyTimer.h>
#include <FlexCAN_T4.h>
#include <StateCAN.h>

#include "Adafruit_GFX.h"
#include "ILI9341_t3n.h"
#include "SPI.h"
#include<string>
using std::string;
#define SPI0_DISP1

// CAN Bus Declaration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;
static CAN_message_t msg;

#define NUM_RX_STD_MAILBOXES 64
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

// CAN Message Definitions
#include "CAN/SR26_CAN2.hpp"

void setup() {
  // Initialize serial communication
  Serial.begin(112500);

  can1.begin();
  // 1mil because this can 1 is only connected to second mm5
  can1.setBaudRate(1000000);
  can2.begin();
  can2.setBaudRate(1000000);
  set_mailboxes();

  // initialize SPI communication
  SPI.begin();
}

void loop() {
  readCan();
  can1.events();
  send_can();
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  can1.setMaxMB(64);  // use all mailboxes of course

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }

  can1.setMBFilter(REJECT_ALL);
  can1.setMBFilter(MB0, MM5F_yawRate.get_msg_id());
  can1.setMBFilter(MB1, MM5F_ay.get_msg_id());
  can1.setMBFilter(MB2, MM5F_rollRate.get_msg_id());
  can1.setMBFilter(MB3, MM5F_ax.get_msg_id()); 
  can1.setMBFilter(MB4, MM5F_az.get_msg_id());
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
}

void readCan() {
  int count = 0;
  while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_SR26_CAN2(rxmsg);
    count++;
  }
}

void send_MM5R_450() {
  static StateCounter ctr;
  msg.id = 450;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = MM5F_yawRate.can_value();
  msg.buf[3] = MM5F_yawRate.can_value() >> 8;
  msg.buf[4] = MM5F_ay.can_value();
  msg.buf[5] = MM5F_ay.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_MM5R_451() {
  static StateCounter ctr;
  msg.id = 451;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = MM5F_rollRate.can_value();
  msg.buf[3] = MM5F_rollRate.can_value() >> 8;
  msg.buf[4] = MM5F_ax.can_value();
  msg.buf[5] = MM5F_ax.can_value() >> 8;
  msg.buf[6] = MM5F_az.can_value();
  msg.buf[7] = MM5F_az.can_value() >> 8;

  can2.write(msg);
}

void send_can() {
  static EasyTimer MM5R_450_timer(100); // 100Hz
  if (MM5R_450_timer.isup()){
    send_MM5R_450();
  }

  static EasyTimer MM5R_451_timer(100); // 100Hz
  if (MM5R_451_timer.isup()){
    send_MM5R_451();
  }
}

#endif