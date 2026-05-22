#include <EasyTimer.h>
#include <FlexCAN_T4.h>
#include <StateCAN.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;

static CAN_message_t raw_msg_372;
static CAN_message_t raw_msg_376;
static CAN_message_t raw_msg_380;

#define NUM_RX_STD_MAILBOXES 64

#include "CAN/SR26_CAN2.hpp"

void setup() {
  Serial.begin(115200);

  can1.begin(); 
  can1.setBaudRate(1000000);
  can2.begin();
  can2.setBaudRate(1000000);
  set_mailboxes();
}

void loop() {
  readCan();
  send_can();
}

void set_mailboxes() {
  can2.setMaxMB(NUM_RX_STD_MAILBOXES); 

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    can2.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }

  can2.setMBFilter(MB0, 372);  // 0x174 (Yaw Rate / ay)
  can2.setMBFilter(MB1, 376);  // 0x178 (Roll Rate / ax)
  can2.setMBFilter(MB2, 380);  // 0x17C (az)

  for (int i = 3; i < NUM_RX_STD_MAILBOXES; i++) {
    can2.setMBFilter((FLEXCAN_MAILBOX)i, REJECT_ALL);
  }
}

void readCan() {
  while (can2.read(rxmsg)) {
    
    if (rxmsg.id == 372) {
      raw_msg_372 = rxmsg;
    } 
    else if (rxmsg.id == 376) {
      raw_msg_376 = rxmsg;
    } 
    else if (rxmsg.id == 380) {
      raw_msg_380 = rxmsg;
    }
    
    decode_SR26_CAN2(rxmsg); 
  }
}

void send_MM52_450() {
  CAN_message_t txmsg = raw_msg_372;
  
  txmsg.id = 450;
  txmsg.len = 8;
  
  can1.write(txmsg);
}

void send_MM52_451() {
  CAN_message_t txmsg;
  txmsg.id = 451;
  txmsg.len = 8;

  txmsg.buf[0] = raw_msg_376.buf[0];
  txmsg.buf[1] = raw_msg_376.buf[1];
  txmsg.buf[2] = raw_msg_376.buf[4];
  txmsg.buf[3] = raw_msg_376.buf[5];
  txmsg.buf[4] = raw_msg_380.buf[4];
  txmsg.buf[5] = raw_msg_380.buf[5];
  txmsg.buf[6] = 0;
  txmsg.buf[7] = 0;

  can1.write(txmsg);
}

void send_can() {
  static EasyTimer MM5R_450_timer(100); // 100Hz
  if (MM5R_450_timer.isup()){
    send_MM52_450();
  }

  static EasyTimer MM5R_451_timer(100); // 100Hz
  if (MM5R_451_timer.isup()){
    send_MM52_451();
  }
}