#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"

// Module1Module1Module1Module1Module1Module1Module1Module1

static CAN_message_t msg;

void send_BMS_500() {
  static StateCounter ctr;
  msg.id = 500;
  msg.len = 8;

  BMS_PackTempoltage = 0;
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
}

void send_BMS_501() {
  static StateCounter ctr;
  msg.id = 501;
  msg.len = 8;

  BMS_Module1V = 0;
  BMS_Module2V = 0;
  BMS_Module3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1V.can_value();
  msg.buf[3] = BMS_Module1V.can_value() >> 8;
  msg.buf[4] = BMS_Module2V.can_value();
  msg.buf[5] = BMS_Module2V.can_value() >> 8;
  msg.buf[6] = BMS_Module3V.can_value();
  msg.buf[7] = BMS_Module3V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_502() {
  static StateCounter ctr;
  msg.id = 502;
  msg.len = 8;

  BMS_Module4V = 0;
  BMS_Module5V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4V.can_value();
  msg.buf[3] = BMS_Module4V.can_value() >> 8;
  msg.buf[4] = BMS_Module5V.can_value();
  msg.buf[5] = BMS_Module5V.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_503() {
  static StateCounter ctr;
  msg.id = 503;
  msg.len = 8;

  BMS_Module1seg1V = 0;
  BMS_Module1seg2V = 0;
  BMS_Module1seg3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg1V.can_value();
  msg.buf[3] = BMS_Module1seg1V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg1V.can_value();
  msg.buf[5] = BMS_Module1seg1V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg1V.can_value();
  msg.buf[7] = BMS_Module1seg1V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_504() {
  static StateCounter ctr;
  msg.id = 504;
  msg.len = 8;

  BMS_Module1seg4V = 0;
  BMS_Module1seg5V = 0;
  BMS_Module1seg6V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg4V.can_value();
  msg.buf[3] = BMS_Module1seg4V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg5V.can_value();
  msg.buf[5] = BMS_Module1seg5V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg6V.can_value();
  msg.buf[7] = BMS_Module1seg6V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_505() {
  static StateCounter ctr;
  msg.id = 505;
  msg.len = 8;

  BMS_Module1seg7V = 0;
  BMS_Module1seg8V = 0;
  BMS_Module1seg9V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg7V.can_value();
  msg.buf[3] = BMS_Module1seg7V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg8V.can_value();
  msg.buf[5] = BMS_Module1seg8V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg9V.can_value();
  msg.buf[7] = BMS_Module1seg9V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_506() {
  static StateCounter ctr;
  msg.id = 506;
  msg.len = 8;

  BMS_Module1seg10V = 0;
  BMS_Module1seg11V = 0;
  BMS_Module1seg12V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg10V.can_value();
  msg.buf[3] = BMS_Module1seg10V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg11V.can_value();
  msg.buf[5] = BMS_Module1seg11V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg12V.can_value();
  msg.buf[7] = BMS_Module1seg12V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_507() {
  static StateCounter ctr;
  msg.id = 507;
  msg.len = 8;

  BMS_Module1seg13V = 0;
  BMS_Module1seg14V = 0;
  BMS_Module1seg15V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg13V.can_value();
  msg.buf[3] = BMS_Module1seg13V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg14V.can_value();
  msg.buf[5] = BMS_Module1seg14V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg15V.can_value();
  msg.buf[7] = BMS_Module1seg15V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_508() {
  static StateCounter ctr;
  msg.id = 508;
  msg.len = 8;

  BMS_Module1seg16V = 0;
  BMS_Module1seg17V = 0;
  BMS_Module1seg18V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg16V.can_value();
  msg.buf[3] = BMS_Module1seg16V.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg17V.can_value();
  msg.buf[5] = BMS_Module1seg17V.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg18V.can_value();
  msg.buf[7] = BMS_Module1seg18V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_509() {
  static StateCounter ctr;
  msg.id = 509;
  msg.len = 8;

  BMS_Module1seg1Temp = 0;
  BMS_Module1seg2Temp = 0;
  BMS_Module1seg3Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg1Temp.can_value();
  msg.buf[3] = BMS_Module1seg1Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg1Temp.can_value();
  msg.buf[5] = BMS_Module1seg1Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg1Temp.can_value();
  msg.buf[7] = BMS_Module1seg1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_510() {
  static StateCounter ctr;
  msg.id = 510;
  msg.len = 8;

  BMS_Module1seg4Temp = 0;
  BMS_Module1seg5Temp = 0;
  BMS_Module1seg6Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg4Temp.can_value();
  msg.buf[3] = BMS_Module1seg4Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg5Temp.can_value();
  msg.buf[5] = BMS_Module1seg5Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg6Temp.can_value();
  msg.buf[7] = BMS_Module1seg6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_511() {
  static StateCounter ctr;
  msg.id = 511;
  msg.len = 8;

  BMS_Module1seg7Temp = 0;
  BMS_Module1seg8Temp = 0;
  BMS_Module1seg9Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg7Temp.can_value();
  msg.buf[3] = BMS_Module1seg7Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg8Temp.can_value();
  msg.buf[5] = BMS_Module1seg8Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg9Temp.can_value();
  msg.buf[7] = BMS_Module1seg9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_512() {
  static StateCounter ctr;
  msg.id = 512;
  msg.len = 8;

  BMS_Module1seg10Temp = 0;
  BMS_Module1seg11Temp = 0;
  BMS_Module1seg12Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg10Temp.can_value();
  msg.buf[3] = BMS_Module1seg10Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg11Temp.can_value();
  msg.buf[5] = BMS_Module1seg11Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg12Temp.can_value();
  msg.buf[7] = BMS_Module1seg12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_513() {
  static StateCounter ctr;
  msg.id = 513;
  msg.len = 8;

  BMS_Module1seg13Temp = 0;
  BMS_Module1seg14Temp = 0;
  BMS_Module1seg15Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg13Temp.can_value();
  msg.buf[3] = BMS_Module1seg13Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg14Temp.can_value();
  msg.buf[5] = BMS_Module1seg14Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg15Temp.can_value();
  msg.buf[7] = BMS_Module1seg15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_514() {
  static StateCounter ctr;
  msg.id = 514;
  msg.len = 8;

  BMS_Module1seg16Temp = 0;
  BMS_Module1seg17Temp = 0;
  BMS_Module1seg18Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module1seg16Temp.can_value();
  msg.buf[3] = BMS_Module1seg16Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module1seg17Temp.can_value();
  msg.buf[5] = BMS_Module1seg17Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module1seg18Temp.can_value();
  msg.buf[7] = BMS_Module1seg18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_515() {
  static StateCounter ctr;
  msg.id = 515;
  msg.len = 8;

  BMS_Module2seg1V = 0;
  BMS_Module2seg2V = 0;
  BMS_Module2seg3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg1V.can_value();
  msg.buf[3] = BMS_Module2seg1V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg1V.can_value();
  msg.buf[5] = BMS_Module2seg1V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg1V.can_value();
  msg.buf[7] = BMS_Module2seg1V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_516() {
  static StateCounter ctr;
  msg.id = 516;
  msg.len = 8;

  BMS_Module2seg4V = 0;
  BMS_Module2seg5V = 0;
  BMS_Module2seg6V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg4V.can_value();
  msg.buf[3] = BMS_Module2seg4V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg5V.can_value();
  msg.buf[5] = BMS_Module2seg5V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg6V.can_value();
  msg.buf[7] = BMS_Module2seg6V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_517() {
  static StateCounter ctr;
  msg.id = 517;
  msg.len = 8;

  BMS_Module2seg7V = 0;
  BMS_Module2seg8V = 0;
  BMS_Module2seg9V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg7V.can_value();
  msg.buf[3] = BMS_Module2seg7V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg8V.can_value();
  msg.buf[5] = BMS_Module2seg8V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg9V.can_value();
  msg.buf[7] = BMS_Module2seg9V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_518() {
  static StateCounter ctr;
  msg.id = 518;
  msg.len = 8;

  BMS_Module2seg10V = 0;
  BMS_Module2seg11V = 0;
  BMS_Module2seg12V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg10V.can_value();
  msg.buf[3] = BMS_Module2seg10V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg11V.can_value();
  msg.buf[5] = BMS_Module2seg11V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg12V.can_value();
  msg.buf[7] = BMS_Module2seg12V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_519() {
  static StateCounter ctr;
  msg.id = 519;
  msg.len = 8;

  BMS_Module2seg13V = 0;
  BMS_Module2seg14V = 0;
  BMS_Module2seg15V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg13V.can_value();
  msg.buf[3] = BMS_Module2seg13V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg14V.can_value();
  msg.buf[5] = BMS_Module2seg14V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg15V.can_value();
  msg.buf[7] = BMS_Module2seg15V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_520() {
  static StateCounter ctr;
  msg.id = 520;
  msg.len = 8;

  BMS_Module2seg16V = 0;
  BMS_Module2seg17V = 0;
  BMS_Module2seg18V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg16V.can_value();
  msg.buf[3] = BMS_Module2seg16V.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg17V.can_value();
  msg.buf[5] = BMS_Module2seg17V.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg18V.can_value();
  msg.buf[7] = BMS_Module2seg18V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_521() {
  static StateCounter ctr;
  msg.id = 521;
  msg.len = 8;

  BMS_Module2seg1Temp = 0;
  BMS_Module2seg2Temp = 0;
  BMS_Module2seg3Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg1Temp.can_value();
  msg.buf[3] = BMS_Module2seg1Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg1Temp.can_value();
  msg.buf[5] = BMS_Module2seg1Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg1Temp.can_value();
  msg.buf[7] = BMS_Module2seg1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_522() {
  static StateCounter ctr;
  msg.id = 522;
  msg.len = 8;

  BMS_Module2seg4Temp = 0;
  BMS_Module2seg5Temp = 0;
  BMS_Module2seg6Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg4Temp.can_value();
  msg.buf[3] = BMS_Module2seg4Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg5Temp.can_value();
  msg.buf[5] = BMS_Module2seg5Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg6Temp.can_value();
  msg.buf[7] = BMS_Module2seg6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_523() {
  static StateCounter ctr;
  msg.id = 523;
  msg.len = 8;

  BMS_Module2seg7Temp = 0;
  BMS_Module2seg8Temp = 0;
  BMS_Module2seg9Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg7Temp.can_value();
  msg.buf[3] = BMS_Module2seg7Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg8Temp.can_value();
  msg.buf[5] = BMS_Module2seg8Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg9Temp.can_value();
  msg.buf[7] = BMS_Module2seg9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_524() {
  static StateCounter ctr;
  msg.id = 524;
  msg.len = 8;

  BMS_Module2seg10Temp = 0;
  BMS_Module2seg11Temp = 0;
  BMS_Module2seg12Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg10Temp.can_value();
  msg.buf[3] = BMS_Module2seg10Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg11Temp.can_value();
  msg.buf[5] = BMS_Module2seg11Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg12Temp.can_value();
  msg.buf[7] = BMS_Module2seg12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_525() {
  static StateCounter ctr;
  msg.id = 525;
  msg.len = 8;

  BMS_Module2seg13Temp = 0;
  BMS_Module2seg14Temp = 0;
  BMS_Module2seg15Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg13Temp.can_value();
  msg.buf[3] = BMS_Module2seg13Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg14Temp.can_value();
  msg.buf[5] = BMS_Module2seg14Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg15Temp.can_value();
  msg.buf[7] = BMS_Module2seg15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_526() {
  static StateCounter ctr;
  msg.id = 526;
  msg.len = 8;

  BMS_Module2seg16Temp = 0;
  BMS_Module2seg17Temp = 0;
  BMS_Module2seg18Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2seg16Temp.can_value();
  msg.buf[3] = BMS_Module2seg16Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module2seg17Temp.can_value();
  msg.buf[5] = BMS_Module2seg17Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module2seg18Temp.can_value();
  msg.buf[7] = BMS_Module2seg18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_527() {
  static StateCounter ctr;
  msg.id = 527;
  msg.len = 8;

  BMS_Module3seg1V = 0;
  BMS_Module3seg2V = 0;
  BMS_Module3seg3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg1V.can_value();
  msg.buf[3] = BMS_Module3seg1V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg1V.can_value();
  msg.buf[5] = BMS_Module3seg1V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg1V.can_value();
  msg.buf[7] = BMS_Module3seg1V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_528() {
  static StateCounter ctr;
  msg.id = 528;
  msg.len = 8;

  BMS_Module3seg4V = 0;
  BMS_Module3seg5V = 0;
  BMS_Module3seg6V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg4V.can_value();
  msg.buf[3] = BMS_Module3seg4V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg5V.can_value();
  msg.buf[5] = BMS_Module3seg5V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg6V.can_value();
  msg.buf[7] = BMS_Module3seg6V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_529() {
  static StateCounter ctr;
  msg.id = 529;
  msg.len = 8;

  BMS_Module3seg7V = 0;
  BMS_Module3seg8V = 0;
  BMS_Module3seg9V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg7V.can_value();
  msg.buf[3] = BMS_Module3seg7V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg8V.can_value();
  msg.buf[5] = BMS_Module3seg8V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg9V.can_value();
  msg.buf[7] = BMS_Module3seg9V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_530() {
  static StateCounter ctr;
  msg.id = 530;
  msg.len = 8;

  BMS_Module3seg10V = 0;
  BMS_Module3seg11V = 0;
  BMS_Module3seg12V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg10V.can_value();
  msg.buf[3] = BMS_Module3seg10V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg11V.can_value();
  msg.buf[5] = BMS_Module3seg11V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg12V.can_value();
  msg.buf[7] = BMS_Module3seg12V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_531() {
  static StateCounter ctr;
  msg.id = 531;
  msg.len = 8;

  BMS_Module3seg13V = 0;
  BMS_Module3seg14V = 0;
  BMS_Module3seg15V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg13V.can_value();
  msg.buf[3] = BMS_Module3seg13V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg14V.can_value();
  msg.buf[5] = BMS_Module3seg14V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg15V.can_value();
  msg.buf[7] = BMS_Module3seg15V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_532() {
  static StateCounter ctr;
  msg.id = 532;
  msg.len = 8;

  BMS_Module3seg16V = 0;
  BMS_Module3seg17V = 0;
  BMS_Module3seg18V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg16V.can_value();
  msg.buf[3] = BMS_Module3seg16V.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg17V.can_value();
  msg.buf[5] = BMS_Module3seg17V.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg18V.can_value();
  msg.buf[7] = BMS_Module3seg18V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_533() {
  static StateCounter ctr;
  msg.id = 533;
  msg.len = 8;

  BMS_Module3seg1Temp = 0;
  BMS_Module3seg2Temp = 0;
  BMS_Module3seg3Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg1Temp.can_value();
  msg.buf[3] = BMS_Module3seg1Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg1Temp.can_value();
  msg.buf[5] = BMS_Module3seg1Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg1Temp.can_value();
  msg.buf[7] = BMS_Module3seg1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_534() {
  static StateCounter ctr;
  msg.id = 534;
  msg.len = 8;

  BMS_Module3seg4Temp = 0;
  BMS_Module3seg5Temp = 0;
  BMS_Module3seg6Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg4Temp.can_value();
  msg.buf[3] = BMS_Module3seg4Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg5Temp.can_value();
  msg.buf[5] = BMS_Module3seg5Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg6Temp.can_value();
  msg.buf[7] = BMS_Module3seg6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_535() {
  static StateCounter ctr;
  msg.id = 535;
  msg.len = 8;

  BMS_Module3seg7Temp = 0;
  BMS_Module3seg8Temp = 0;
  BMS_Module3seg9Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg7Temp.can_value();
  msg.buf[3] = BMS_Module3seg7Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg8Temp.can_value();
  msg.buf[5] = BMS_Module3seg8Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg9Temp.can_value();
  msg.buf[7] = BMS_Module3seg9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_536() {
  static StateCounter ctr;
  msg.id = 536;
  msg.len = 8;

  BMS_Module3seg10Temp = 0;
  BMS_Module3seg11Temp = 0;
  BMS_Module3seg12Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg10Temp.can_value();
  msg.buf[3] = BMS_Module3seg10Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg11Temp.can_value();
  msg.buf[5] = BMS_Module3seg11Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg12Temp.can_value();
  msg.buf[7] = BMS_Module3seg12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_537() {
  static StateCounter ctr;
  msg.id = 537;
  msg.len = 8;

  BMS_Module3seg13Temp = 0;
  BMS_Module3seg14Temp = 0;
  BMS_Module3seg15Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg13Temp.can_value();
  msg.buf[3] = BMS_Module3seg13Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg14Temp.can_value();
  msg.buf[5] = BMS_Module3seg14Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg15Temp.can_value();
  msg.buf[7] = BMS_Module3seg15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_538() {
  static StateCounter ctr;
  msg.id = 538;
  msg.len = 8;

  BMS_Module3seg16Temp = 0;
  BMS_Module3seg17Temp = 0;
  BMS_Module3seg18Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module3seg16Temp.can_value();
  msg.buf[3] = BMS_Module3seg16Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module3seg17Temp.can_value();
  msg.buf[5] = BMS_Module3seg17Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module3seg18Temp.can_value();
  msg.buf[7] = BMS_Module3seg18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_539() {
  static StateCounter ctr;
  msg.id = 539;
  msg.len = 8;

  BMS_Module4seg1V = 0;
  BMS_Module4seg2V = 0;
  BMS_Module4seg3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg1V.can_value();
  msg.buf[3] = BMS_Module4seg1V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg1V.can_value();
  msg.buf[5] = BMS_Module4seg1V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg1V.can_value();
  msg.buf[7] = BMS_Module4seg1V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_540() {
  static StateCounter ctr;
  msg.id = 540;
  msg.len = 8;

  BMS_Module4seg4V = 0;
  BMS_Module4seg5V = 0;
  BMS_Module4seg6V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg4V.can_value();
  msg.buf[3] = BMS_Module4seg4V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg5V.can_value();
  msg.buf[5] = BMS_Module4seg5V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg6V.can_value();
  msg.buf[7] = BMS_Module4seg6V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_541() {
  static StateCounter ctr;
  msg.id = 541;
  msg.len = 8;

  BMS_Module4seg7V = 0;
  BMS_Module4seg8V = 0;
  BMS_Module4seg9V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg7V.can_value();
  msg.buf[3] = BMS_Module4seg7V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg8V.can_value();
  msg.buf[5] = BMS_Module4seg8V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg9V.can_value();
  msg.buf[7] = BMS_Module4seg9V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_542() {
  static StateCounter ctr;
  msg.id = 542;
  msg.len = 8;

  BMS_Module4seg10V = 0;
  BMS_Module4seg11V = 0;
  BMS_Module4seg12V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg10V.can_value();
  msg.buf[3] = BMS_Module4seg10V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg11V.can_value();
  msg.buf[5] = BMS_Module4seg11V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg12V.can_value();
  msg.buf[7] = BMS_Module4seg12V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_543() {
  static StateCounter ctr;
  msg.id = 543;
  msg.len = 8;

  BMS_Module4seg13V = 0;
  BMS_Module4seg14V = 0;
  BMS_Module4seg15V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg13V.can_value();
  msg.buf[3] = BMS_Module4seg13V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg14V.can_value();
  msg.buf[5] = BMS_Module4seg14V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg15V.can_value();
  msg.buf[7] = BMS_Module4seg15V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_544() {
  static StateCounter ctr;
  msg.id = 544;
  msg.len = 8;

  BMS_Module4seg16V = 0;
  BMS_Module4seg17V = 0;
  BMS_Module4seg18V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg16V.can_value();
  msg.buf[3] = BMS_Module4seg16V.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg17V.can_value();
  msg.buf[5] = BMS_Module4seg17V.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg18V.can_value();
  msg.buf[7] = BMS_Module4seg18V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_545() {
  static StateCounter ctr;
  msg.id = 545;
  msg.len = 8;

  BMS_Module4seg1Temp = 0;
  BMS_Module4seg2Temp = 0;
  BMS_Module4seg3Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg1Temp.can_value();
  msg.buf[3] = BMS_Module4seg1Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg1Temp.can_value();
  msg.buf[5] = BMS_Module4seg1Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg1Temp.can_value();
  msg.buf[7] = BMS_Module4seg1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_546() {
  static StateCounter ctr;
  msg.id = 546;
  msg.len = 8;

  BMS_Module4seg4Temp = 0;
  BMS_Module4seg5Temp = 0;
  BMS_Module4seg6Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg4Temp.can_value();
  msg.buf[3] = BMS_Module4seg4Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg5Temp.can_value();
  msg.buf[5] = BMS_Module4seg5Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg6Temp.can_value();
  msg.buf[7] = BMS_Module4seg6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_547() {
  static StateCounter ctr;
  msg.id = 547;
  msg.len = 8;

  BMS_Module4seg7Temp = 0;
  BMS_Module4seg8Temp = 0;
  BMS_Module4seg9Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg7Temp.can_value();
  msg.buf[3] = BMS_Module4seg7Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg8Temp.can_value();
  msg.buf[5] = BMS_Module4seg8Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg9Temp.can_value();
  msg.buf[7] = BMS_Module4seg9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_548() {
  static StateCounter ctr;
  msg.id = 548;
  msg.len = 8;

  BMS_Module4seg10Temp = 0;
  BMS_Module4seg11Temp = 0;
  BMS_Module4seg12Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg10Temp.can_value();
  msg.buf[3] = BMS_Module4seg10Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg11Temp.can_value();
  msg.buf[5] = BMS_Module4seg11Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg12Temp.can_value();
  msg.buf[7] = BMS_Module4seg12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_549() {
  static StateCounter ctr;
  msg.id = 549;
  msg.len = 8;

  BMS_Module4seg13Temp = 0;
  BMS_Module4seg14Temp = 0;
  BMS_Module4seg15Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg13Temp.can_value();
  msg.buf[3] = BMS_Module4seg13Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg14Temp.can_value();
  msg.buf[5] = BMS_Module4seg14Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg15Temp.can_value();
  msg.buf[7] = BMS_Module4seg15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_550() {
  static StateCounter ctr;
  msg.id = 550;
  msg.len = 8;

  BMS_Module4seg16Temp = 0;
  BMS_Module4seg17Temp = 0;
  BMS_Module4seg18Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module4seg16Temp.can_value();
  msg.buf[3] = BMS_Module4seg16Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module4seg17Temp.can_value();
  msg.buf[5] = BMS_Module4seg17Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module4seg18Temp.can_value();
  msg.buf[7] = BMS_Module4seg18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_551() {
  static StateCounter ctr;
  msg.id = 551;
  msg.len = 8;

  BMS_Module5seg1V = 0;
  BMS_Module5seg2V = 0;
  BMS_Module5seg3V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg1V.can_value();
  msg.buf[3] = BMS_Module5seg1V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg1V.can_value();
  msg.buf[5] = BMS_Module5seg1V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg1V.can_value();
  msg.buf[7] = BMS_Module5seg1V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_552() {
  static StateCounter ctr;
  msg.id = 552;
  msg.len = 8;

  BMS_Module5seg4V = 0;
  BMS_Module5seg5V = 0;
  BMS_Module5seg6V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg4V.can_value();
  msg.buf[3] = BMS_Module5seg4V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg5V.can_value();
  msg.buf[5] = BMS_Module5seg5V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg6V.can_value();
  msg.buf[7] = BMS_Module5seg6V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_553() {
  static StateCounter ctr;
  msg.id = 553;
  msg.len = 8;

  BMS_Module5seg7V = 0;
  BMS_Module5seg8V = 0;
  BMS_Module5seg9V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg7V.can_value();
  msg.buf[3] = BMS_Module5seg7V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg8V.can_value();
  msg.buf[5] = BMS_Module5seg8V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg9V.can_value();
  msg.buf[7] = BMS_Module5seg9V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_554() {
  static StateCounter ctr;
  msg.id = 554;
  msg.len = 8;

  BMS_Module5seg10V = 0;
  BMS_Module5seg11V = 0;
  BMS_Module5seg12V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg10V.can_value();
  msg.buf[3] = BMS_Module5seg10V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg11V.can_value();
  msg.buf[5] = BMS_Module5seg11V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg12V.can_value();
  msg.buf[7] = BMS_Module5seg12V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_555() {
  static StateCounter ctr;
  msg.id = 555;
  msg.len = 8;

  BMS_Module5seg13V = 0;
  BMS_Module5seg14V = 0;
  BMS_Module5seg15V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg13V.can_value();
  msg.buf[3] = BMS_Module5seg13V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg14V.can_value();
  msg.buf[5] = BMS_Module5seg14V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg15V.can_value();
  msg.buf[7] = BMS_Module5seg15V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_556() {
  static StateCounter ctr;
  msg.id = 556;
  msg.len = 8;

  BMS_Module5seg16V = 0;
  BMS_Module5seg17V = 0;
  BMS_Module5seg18V = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg16V.can_value();
  msg.buf[3] = BMS_Module5seg16V.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg17V.can_value();
  msg.buf[5] = BMS_Module5seg17V.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg18V.can_value();
  msg.buf[7] = BMS_Module5seg18V.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_557() {
  static StateCounter ctr;
  msg.id = 557;
  msg.len = 8;

  BMS_Module5seg1Temp = 0;
  BMS_Module5seg2Temp = 0;
  BMS_Module5seg3Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg1Temp.can_value();
  msg.buf[3] = BMS_Module5seg1Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg1Temp.can_value();
  msg.buf[5] = BMS_Module5seg1Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg1Temp.can_value();
  msg.buf[7] = BMS_Module5seg1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_558() {
  static StateCounter ctr;
  msg.id = 558;
  msg.len = 8;

  BMS_Module5seg4Temp = 0;
  BMS_Module5seg5Temp = 0;
  BMS_Module5seg6Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg4Temp.can_value();
  msg.buf[3] = BMS_Module5seg4Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg5Temp.can_value();
  msg.buf[5] = BMS_Module5seg5Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg6Temp.can_value();
  msg.buf[7] = BMS_Module5seg6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_559() {
  static StateCounter ctr;
  msg.id = 559;
  msg.len = 8;

  BMS_Module5seg7Temp = 0;
  BMS_Module5seg8Temp = 0;
  BMS_Module5seg9Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg7Temp.can_value();
  msg.buf[3] = BMS_Module5seg7Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg8Temp.can_value();
  msg.buf[5] = BMS_Module5seg8Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg9Temp.can_value();
  msg.buf[7] = BMS_Module5seg9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_560() {
  static StateCounter ctr;
  msg.id = 560;
  msg.len = 8;

  BMS_Module5seg10Temp = 0;
  BMS_Module5seg11Temp = 0;
  BMS_Module5seg12Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg10Temp.can_value();
  msg.buf[3] = BMS_Module5seg10Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg11Temp.can_value();
  msg.buf[5] = BMS_Module5seg11Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg12Temp.can_value();
  msg.buf[7] = BMS_Module5seg12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_561() {
  static StateCounter ctr;
  msg.id = 561;
  msg.len = 8;

  BMS_Module5seg13Temp = 0;
  BMS_Module5seg14Temp = 0;
  BMS_Module5seg15Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg13Temp.can_value();
  msg.buf[3] = BMS_Module5seg13Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg14Temp.can_value();
  msg.buf[5] = BMS_Module5seg14Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg15Temp.can_value();
  msg.buf[7] = BMS_Module5seg15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_562() {
  static StateCounter ctr;
  msg.id = 562;
  msg.len = 8;

  BMS_Module5seg16Temp = 0;
  BMS_Module5seg17Temp = 0;
  BMS_Module5seg18Temp = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module5seg16Temp.can_value();
  msg.buf[3] = BMS_Module5seg16Temp.can_value() >> 8;
  msg.buf[4] = BMS_Module5seg17Temp.can_value();
  msg.buf[5] = BMS_Module5seg17Temp.can_value() >> 8;
  msg.buf[6] = BMS_Module5seg18Temp.can_value();
  msg.buf[7] = BMS_Module5seg18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_can_2() {

  static EasyTime BMS_500_timer(10); // 10Hz for 100ms message interval
  if (BMS_500_timer.isup()) {
    send_BMS_500();
  }

  static EasyTime BMS_501_timer(10); // 10Hz for 100ms message interval
  if (BMS_501_timer.isup()) {
    send_BMS_501();
  }

  static EasyTime BMS_502_timer(10); // 10Hz for 100ms message interval
  if (BMS_502_timer.isup()) {
    send_BMS_502();
  }

  static EasyTime BMS_503_timer(10); // 10Hz for 100ms message interval
  if (BMS_503_timer.isup()) {
    send_BMS_503();
  }

  static EasyTime BMS_504_timer(10); // 10Hz for 100ms message interval
  if (BMS_504_timer.isup()) {
    send_BMS_504();
  }
  static EasyTime BMS_505_timer(10); // 10Hz for 100ms message interval
  if (BMS_505_timer.isup()) {
    send_BMS_505();
  }

  static EasyTime BMS_506_timer(10); // 10Hz for 100ms message interval
  if (BMS_506_timer.isup()) {
    send_BMS_506();
  }

  static EasyTime BMS_507_timer(10); // 10Hz for 100ms message interval
  if (BMS_507_timer.isup()) {
    send_BMS_507();
  }

  static EasyTime BMS_508_timer(10); // 10Hz for 100ms message interval
  if (BMS_508_timer.isup()) {
    send_BMS_508();
  }

  static EasyTime BMS_509_timer(1); // 10Hz for 100ms message interval
  if (BMS_509_timer.isup()) {
    send_BMS_509();
  }

  static EasyTime BMS_510_timer(1); // 10Hz for 100ms message interval
  if (BMS_510_timer.isup()) {
    send_BMS_510();
  }

  static EasyTime BMS_511_timer(1); // 10Hz for 100ms message interval
  if (BMS_511_timer.isup()) {
    send_BMS_511();
  }

  static EasyTime BMS_512_timer(10); // 10Hz for 100ms message interval
  if (BMS_512_timer.isup()) {
    send_BMS_512();
  }

  static EasyTime BMS_513_timer(1); // 10Hz for 100ms message interval
  if (BMS_513_timer.isup()) {
    send_BMS_513();
  }

  static EasyTime BMS_514_timer(1); // 10Hz for 100ms message interval
  if (BMS_514_timer.isup()) {
    send_BMS_514();
  }
  static EasyTime BMS_515_timer(10); // 10Hz for 100ms message interval
  if (BMS_515_timer.isup()) {
    send_BMS_515();
  }

  static EasyTime BMS_516_timer(10); // 10Hz for 100ms message interval
  if (BMS_516_timer.isup()) {
    send_BMS_516();
  }

  static EasyTime BMS_517_timer(10); // 10Hz for 100ms message interval
  if (BMS_517_timer.isup()) {
    send_BMS_517();
  }

  static EasyTime BMS_518_timer(10); // 10Hz for 100ms message interval
  if (BMS_518_timer.isup()) {
    send_BMS_518();
  }

  static EasyTime BMS_519_timer(10); // 10Hz for 100ms message interval
  if (BMS_519_timer.isup()) {
    send_BMS_519();
  }

  static EasyTime BMS_520_timer(10); // 10Hz for 100ms message interval
  if (BMS_520_timer.isup()) {
    send_BMS_520();
  }

  static EasyTime BMS_521_timer(1); // 10Hz for 100ms message interval
  if (BMS_521_timer.isup()) {
    send_BMS_521();
  }

  static EasyTime BMS_522_timer(1); // 10Hz for 100ms message interval
  if (BMS_522_timer.isup()) {
    send_BMS_522();
  }

  static EasyTime BMS_523_timer(1); // 10Hz for 100ms message interval
  if (BMS_523_timer.isup()) {
    send_BMS_523();
  }

  static EasyTime BMS_524_timer(1); // 10Hz for 100ms message interval
  if (BMS_524_timer.isup()) {
    send_BMS_524();
  }
  static EasyTime BMS_525_timer(1); // 10Hz for 100ms message interval
  if (BMS_525_timer.isup()) {
    send_BMS_525();
  }

  static EasyTime BMS_526_timer(1); // 10Hz for 100ms message interval
  if (BMS_526_timer.isup()) {
    send_BMS_526();
  }

  static EasyTime BMS_527_timer(10); // 10Hz for 100ms message interval
  if (BMS_527_timer.isup()) {
    send_BMS_527();
  }

  static EasyTime BMS_528_timer(10); // 10Hz for 100ms message interval
  if (BMS_528_timer.isup()) {
    send_BMS_528();
  }

  static EasyTime BMS_529_timer(10); // 10Hz for 100ms message interval
  if (BMS_529_timer.isup()) {
    send_BMS_529();
  }

  static EasyTime BMS_530_timer(10); // 10Hz for 100ms message interval
  if (BMS_530_timer.isup()) {
    send_BMS_530();
  }

  static EasyTime BMS_531_timer(10); // 10Hz for 100ms message interval
  if (BMS_531_timer.isup()) {
    send_BMS_531();
  }

  static EasyTime BMS_532_timer(10); // 10Hz for 100ms message interval
  if (BMS_532_timer.isup()) {
    send_BMS_532();
  }

  static EasyTime BMS_533_timer(1); // 10Hz for 100ms message interval
  if (BMS_533_timer.isup()) {
    send_BMS_533();
  }

  static EasyTime BMS_534_timer(1); // 10Hz for 100ms message interval
  if (BMS_534_timer.isup()) {
    send_BMS_534();
  }
  static EasyTime BMS_535_timer(1); // 10Hz for 100ms message interval
  if (BMS_535_timer.isup()) {
    send_BMS_535();
  }

  static EasyTime BMS_536_timer(1); // 10Hz for 100ms message interval
  if (BMS_536_timer.isup()) {
    send_BMS_536();
  }

  static EasyTime BMS_537_timer(1); // 10Hz for 100ms message interval
  if (BMS_537_timer.isup()) {
    send_BMS_537();
  }

  static EasyTime BMS_538_timer(1); // 10Hz for 100ms message interval
  if (BMS_538_timer.isup()) {
    send_BMS_538();
  }

  static EasyTime BMS_539_timer(10); // 10Hz for 100ms message interval
  if (BMS_539_timer.isup()) {
    send_BMS_539();
  }

  static EasyTime BMS_540_timer(10); // 10Hz for 100ms message interval
  if (BMS_540_timer.isup()) {
    send_BMS_540();
  }

  static EasyTime BMS_541_timer(10); // 10Hz for 100ms message interval
  if (BMS_541_timer.isup()) {
    send_BMS_541();
  }

  static EasyTime BMS_542_timer(10); // 10Hz for 100ms message interval
  if (BMS_542_timer.isup()) {
    send_BMS_542();
  }

  static EasyTime BMS_543_timer(10); // 10Hz for 100ms message interval
  if (BMS_543_timer.isup()) {
    send_BMS_543();
  }

  static EasyTime BMS_544_timer(10); // 10Hz for 100ms message interval
  if (BMS_544_timer.isup()) {
    send_BMS_544();
  }
  static EasyTime BMS_545_timer(1); // 10Hz for 100ms message interval
  if (BMS_545_timer.isup()) {
    send_BMS_545();
  }

  static EasyTime BMS_546_timer(1); // 10Hz for 100ms message interval
  if (BMS_546_timer.isup()) {
    send_BMS_546();
  }

  static EasyTime BMS_547_timer(1); // 10Hz for 100ms message interval
  if (BMS_547_timer.isup()) {
    send_BMS_547();
  }

  static EasyTime BMS_548_timer(1); // 10Hz for 100ms message interval
  if (BMS_548_timer.isup()) {
    send_BMS_548();
  }

  static EasyTime BMS_549_timer(1); // 10Hz for 100ms message interval
  if (BMS_549_timer.isup()) {
    send_BMS_549();
  }

  static EasyTime BMS_550_timer(1); // 10Hz for 100ms message interval
  if (BMS_550_timer.isup()) {
    send_BMS_550();
  }

  static EasyTime BMS_551_timer(10); // 10Hz for 100ms message interval
  if (BMS_551_timer.isup()) {
    send_BMS_551();
  }

  static EasyTime BMS_552_timer(10); // 10Hz for 100ms message interval
  if (BMS_552_timer.isup()) {
    send_BMS_552();
  }

  static EasyTime BMS_553_timer(10); // 10Hz for 100ms message interval
  if (BMS_553_timer.isup()) {
    send_BMS_553();
  }

  static EasyTime BMS_554_timer(10); // 10Hz for 100ms message interval
  if (BMS_554_timer.isup()) {
    send_BMS_554();
  }
  static EasyTime BMS_555_timer(10); // 10Hz for 100ms message interval
  if (BMS_555_timer.isup()) {
    send_BMS_555();
  }

  static EasyTime BMS_556_timer(10); // 10Hz for 100ms message interval
  if (BMS_556_timer.isup()) {
    send_BMS_556();
  }

  static EasyTime BMS_557_timer(1); // 10Hz for 100ms message interval
  if (BMS_557_timer.isup()) {
    send_BMS_557();
  }

  static EasyTime BMS_558_timer(1); // 10Hz for 100ms message interval
  if (BMS_558_timer.isup()) {
    send_BMS_558();
  }

  static EasyTime BMS_559_timer(1); // 10Hz for 100ms message interval
  if (BMS_559_timer.isup()) {
    send_BMS_559();
  }

  static EasyTime BMS_560_timer(1); // 10Hz for 100ms message interval
  if (BMS_560_timer.isup()) {
    send_BMS_560();
  }

  static EasyTime BMS_561_timer(1); // 10Hz for 100ms message interval
  if (BMS_561_timer.isup()) {
    send_BMS_561();
  }

  static EasyTime BMS_562_timer(1); // 10Hz for 100ms message interval
  if (BMS_562_timer.isup()) {
    send_BMS_562();
  }

}