#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"


// Module1Module1Module1Module1Module1Module1Module1Module1

static CAN_message_t msg;

void send_BMS_TEST_500() {
  static StateCounter ctr;
  msg.id = 500;
  msg.len = 8;

  BMS_PackVoltage = 0;
  BMS_PackCurrent = 0;
  BMS_PackSOC = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_PackVoltage.can_value();
  msg.buf[3] = BMS_PackVoltage.can_value() >> 8;
  msg.buf[4] = BMS_PackCurrent.can_value();
  msg.buf[5] = BMS_PackCurrent.can_value() >> 8;
  msg.buf[6] = BMS_PackSOC.can_value();
  msg.buf[7] = BMS_PackSOC.can_value() >> 8;

  can2.write(msg);

  Serial.println("sending test can message");
}

void test_can() {
  static EasyTimer BMS_500_timer(20); // 10Hz for 100ms message interval
  if (BMS_500_timer.isup()) {
    send_BMS_500();
  }
}

#endif