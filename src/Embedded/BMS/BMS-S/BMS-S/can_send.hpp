

#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"


const int MODULE_2 = 5; // BMS-S select, 1-5

static CAN_message_t msg;

void send_BMS_500() {
  static StateCounter ctr;
  msg.id = 500;
  msg.len = 8;

  BMS_packmVoltage = 0;
  BMS_packCurrent = 0;
  BMS_packSOC = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_packmVoltage.can_value();
  msg.buf[3] = BMS_packmVoltage.can_value() >> 8;
  msg.buf[4] = BMS_packCurrent.can_value();
  msg.buf[5] = BMS_packCurrent.can_value() >> 8;
  msg.buf[6] = BMS_packSOC.can_value();
  msg.buf[7] = BMS_packSOC.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_501() {
  static StateCounter ctr;
  msg.id = 501;
  msg.len = 8;

  BMS_module1Volt = 0;
  BMS_module2Volt = 0;
  BMS_module3Volt = 0;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Volt.can_value();
  msg.buf[3] = BMS_module2Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Volt.can_value();
  msg.buf[5] = BMS_module2Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Volt.can_value();
  msg.buf[7] = BMS_module3Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_502() {
  static StateCounter ctr;
  msg.id = 502;
  msg.len = 8;

  BMS_module4Volt = 0;
  BMS_module5Volt = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Volt.can_value();
  msg.buf[3] = BMS_module4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Volt.can_value();
  msg.buf[5] = BMS_module5Volt.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_503() {
  static StateCounter ctr;
  msg.id = 503;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell1Volt.can_value();
  msg.buf[3] = BMS_module1Cell1Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell1Volt.can_value();
  msg.buf[5] = BMS_module1Cell1Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell1Volt.can_value();
  msg.buf[7] = BMS_module1Cell1Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_504() {
  static StateCounter ctr;
  msg.id = 504;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell4Volt.can_value();
  msg.buf[3] = BMS_module1Cell4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell5Volt.can_value();
  msg.buf[5] = BMS_module1Cell5Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell6Volt.can_value();
  msg.buf[7] = BMS_module1Cell6Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_505() {
  static StateCounter ctr;
  msg.id = 505;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell7Volt.can_value();
  msg.buf[3] = BMS_module1Cell7Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell8Volt.can_value();
  msg.buf[5] = BMS_module1Cell8Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell9Volt.can_value();
  msg.buf[7] = BMS_module1Cell9Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_506() {
  static StateCounter ctr;
  msg.id = 506;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell10Volt.can_value();
  msg.buf[3] = BMS_module1Cell10Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell11Volt.can_value();
  msg.buf[5] = BMS_module1Cell11Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell12Volt.can_value();
  msg.buf[7] = BMS_module1Cell12Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_507() {
  static StateCounter ctr;
  msg.id = 507;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell13Volt.can_value();
  msg.buf[3] = BMS_module1Cell13Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell14Volt.can_value();
  msg.buf[5] = BMS_module1Cell14Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell15Volt.can_value();
  msg.buf[7] = BMS_module1Cell15Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_508() {
  static StateCounter ctr;
  msg.id = 508;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell16Volt.can_value();
  msg.buf[3] = BMS_module1Cell16Volt.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell17Volt.can_value();
  msg.buf[5] = BMS_module1Cell17Volt.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell18Volt.can_value();
  msg.buf[7] = BMS_module1Cell18Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_509() {
  static StateCounter ctr;
  msg.id = 509;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell1Temp.can_value();
  msg.buf[3] = BMS_module1Cell1Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell1Temp.can_value();
  msg.buf[5] = BMS_module1Cell1Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell1Temp.can_value();
  msg.buf[7] = BMS_module1Cell1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_510() {
  static StateCounter ctr;
  msg.id = 510;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell4Temp.can_value();
  msg.buf[3] = BMS_module1Cell4Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell5Temp.can_value();
  msg.buf[5] = BMS_module1Cell5Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell6Temp.can_value();
  msg.buf[7] = BMS_module1Cell6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_511() {
  static StateCounter ctr;
  msg.id = 511;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell7Temp.can_value();
  msg.buf[3] = BMS_module1Cell7Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell8Temp.can_value();
  msg.buf[5] = BMS_module1Cell8Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell9Temp.can_value();
  msg.buf[7] = BMS_module1Cell9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_512() {
  static StateCounter ctr;
  msg.id = 512;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell10Temp.can_value();
  msg.buf[3] = BMS_module1Cell10Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell11Temp.can_value();
  msg.buf[5] = BMS_module1Cell11Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell12Temp.can_value();
  msg.buf[7] = BMS_module1Cell12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_513() {
  static StateCounter ctr;
  msg.id = 513;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell13Temp.can_value();
  msg.buf[3] = BMS_module1Cell13Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell14Temp.can_value();
  msg.buf[5] = BMS_module1Cell14Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell15Temp.can_value();
  msg.buf[7] = BMS_module1Cell15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_514() {
  static StateCounter ctr;
  msg.id = 514;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1Cell16Temp.can_value();
  msg.buf[3] = BMS_module1Cell16Temp.can_value() >> 8;
  msg.buf[4] = BMS_module1Cell17Temp.can_value();
  msg.buf[5] = BMS_module1Cell17Temp.can_value() >> 8;
  msg.buf[6] = BMS_module1Cell18Temp.can_value();
  msg.buf[7] = BMS_module1Cell18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_515() {
  static StateCounter ctr;
  msg.id = 515;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell1Volt.can_value();
  msg.buf[3] = BMS_module2Cell1Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell1Volt.can_value();
  msg.buf[5] = BMS_module2Cell1Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell1Volt.can_value();
  msg.buf[7] = BMS_module2Cell1Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_516() {
  static StateCounter ctr;
  msg.id = 516;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell4Volt.can_value();
  msg.buf[3] = BMS_module2Cell4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell5Volt.can_value();
  msg.buf[5] = BMS_module2Cell5Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell6Volt.can_value();
  msg.buf[7] = BMS_module2Cell6Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_517() {
  static StateCounter ctr;
  msg.id = 517;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell7Volt.can_value();
  msg.buf[3] = BMS_module2Cell7Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell8Volt.can_value();
  msg.buf[5] = BMS_module2Cell8Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell9Volt.can_value();
  msg.buf[7] = BMS_module2Cell9Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_518() {
  static StateCounter ctr;
  msg.id = 518;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell10Volt.can_value();
  msg.buf[3] = BMS_module2Cell10Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell11Volt.can_value();
  msg.buf[5] = BMS_module2Cell11Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell12Volt.can_value();
  msg.buf[7] = BMS_module2Cell12Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_519() {
  static StateCounter ctr;
  msg.id = 519;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell13Volt.can_value();
  msg.buf[3] = BMS_module2Cell13Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell14Volt.can_value();
  msg.buf[5] = BMS_module2Cell14Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell15Volt.can_value();
  msg.buf[7] = BMS_module2Cell15Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_520() {
  static StateCounter ctr;
  Serial.println("Send_BMS_520");
  msg.id = 520;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell16Volt.can_value();
  msg.buf[3] = BMS_module2Cell16Volt.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell17Volt.can_value();
  msg.buf[5] = BMS_module2Cell17Volt.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell18Volt.can_value();
  msg.buf[7] = BMS_module2Cell18Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_521() {
  static StateCounter ctr;
  msg.id = 521;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell1Temp.can_value();
  msg.buf[3] = BMS_module2Cell1Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell1Temp.can_value();
  msg.buf[5] = BMS_module2Cell1Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell1Temp.can_value();
  msg.buf[7] = BMS_module2Cell1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_522() {
  static StateCounter ctr;
  msg.id = 522;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell4Temp.can_value();
  msg.buf[3] = BMS_module2Cell4Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell5Temp.can_value();
  msg.buf[5] = BMS_module2Cell5Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell6Temp.can_value();
  msg.buf[7] = BMS_module2Cell6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_523() {
  static StateCounter ctr;
  msg.id = 523;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell7Temp.can_value();
  msg.buf[3] = BMS_module2Cell7Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell8Temp.can_value();
  msg.buf[5] = BMS_module2Cell8Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell9Temp.can_value();
  msg.buf[7] = BMS_module2Cell9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_524() {
  static StateCounter ctr;
  msg.id = 524;
  msg.len = 8;

  

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell10Temp.can_value();
  msg.buf[3] = BMS_module2Cell10Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell11Temp.can_value();
  msg.buf[5] = BMS_module2Cell11Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell12Temp.can_value();
  msg.buf[7] = BMS_module2Cell12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_525() {
  static StateCounter ctr;
  msg.id = 525;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_Module2Cell13Temp.can_value();
  msg.buf[3] = BMS_Module2Cell13Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell14Temp.can_value();
  msg.buf[5] = BMS_module2Cell14Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell15Temp.can_value();
  msg.buf[7] = BMS_module2Cell15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_526() {
  static StateCounter ctr;
  msg.id = 526;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2Cell16Temp.can_value();
  msg.buf[3] = BMS_module2Cell16Temp.can_value() >> 8;
  msg.buf[4] = BMS_module2Cell17Temp.can_value();
  msg.buf[5] = BMS_module2Cell17Temp.can_value() >> 8;
  msg.buf[6] = BMS_module2Cell18Temp.can_value();
  msg.buf[7] = BMS_module2Cell18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_527() {
  static StateCounter ctr;
  msg.id = 527;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell1Volt.can_value();
  msg.buf[3] = BMS_module3Cell1Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell1Volt.can_value();
  msg.buf[5] = BMS_module3Cell1Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell1Volt.can_value();
  msg.buf[7] = BMS_module3Cell1Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_528() {
  static StateCounter ctr;
  msg.id = 528;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell4Volt.can_value();
  msg.buf[3] = BMS_module3Cell4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell5Volt.can_value();
  msg.buf[5] = BMS_module3Cell5Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell6Volt.can_value();
  msg.buf[7] = BMS_module3Cell6Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_529() {
  static StateCounter ctr;
  msg.id = 529;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell7Volt.can_value();
  msg.buf[3] = BMS_module3Cell7Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell8Volt.can_value();
  msg.buf[5] = BMS_module3Cell8Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell9Volt.can_value();
  msg.buf[7] = BMS_module3Cell9Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_530() {
  static StateCounter ctr;
  msg.id = 530;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell10Volt.can_value();
  msg.buf[3] = BMS_module3Cell10Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell11Volt.can_value();
  msg.buf[5] = BMS_module3Cell11Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell12Volt.can_value();
  msg.buf[7] = BMS_module3Cell12Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_531() {
  static StateCounter ctr;
  msg.id = 531;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell13Volt.can_value();
  msg.buf[3] = BMS_module3Cell13Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell14Volt.can_value();
  msg.buf[5] = BMS_module3Cell14Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell15Volt.can_value();
  msg.buf[7] = BMS_module3Cell15Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_532() {
  static StateCounter ctr;
  msg.id = 532;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell16Volt.can_value();
  msg.buf[3] = BMS_module3Cell16Volt.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell17Volt.can_value();
  msg.buf[5] = BMS_module3Cell17Volt.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell18Volt.can_value();
  msg.buf[7] = BMS_module3Cell18Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_533() {
  static StateCounter ctr;
  msg.id = 533;
  msg.len = 8;

 

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell1Temp.can_value();
  msg.buf[3] = BMS_module3Cell1Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell1Temp.can_value();
  msg.buf[5] = BMS_module3Cell1Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell1Temp.can_value();
  msg.buf[7] = BMS_module3Cell1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_534() {
  static StateCounter ctr;
  msg.id = 534;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell4Temp.can_value();
  msg.buf[3] = BMS_module3Cell4Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell5Temp.can_value();
  msg.buf[5] = BMS_module3Cell5Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell6Temp.can_value();
  msg.buf[7] = BMS_module3Cell6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_535() {
  static StateCounter ctr;
  msg.id = 535;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell7Temp.can_value();
  msg.buf[3] = BMS_module3Cell7Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell8Temp.can_value();
  msg.buf[5] = BMS_module3Cell8Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell9Temp.can_value();
  msg.buf[7] = BMS_module3Cell9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_536() {
  static StateCounter ctr;
  msg.id = 536;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell10Temp.can_value();
  msg.buf[3] = BMS_module3Cell10Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell11Temp.can_value();
  msg.buf[5] = BMS_module3Cell11Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell12Temp.can_value();
  msg.buf[7] = BMS_module3Cell12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_537() {
  static StateCounter ctr;
  msg.id = 537;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell13Temp.can_value();
  msg.buf[3] = BMS_module3Cell13Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell14Temp.can_value();
  msg.buf[5] = BMS_module3Cell14Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell15Temp.can_value();
  msg.buf[7] = BMS_module3Cell15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_538() {
  static StateCounter ctr;
  msg.id = 538;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3Cell16Temp.can_value();
  msg.buf[3] = BMS_module3Cell16Temp.can_value() >> 8;
  msg.buf[4] = BMS_module3Cell17Temp.can_value();
  msg.buf[5] = BMS_module3Cell17Temp.can_value() >> 8;
  msg.buf[6] = BMS_module3Cell18Temp.can_value();
  msg.buf[7] = BMS_module3Cell18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_539() {
  static StateCounter ctr;
  msg.id = 539;
  msg.len = 8;

  

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell1Volt.can_value();
  msg.buf[3] = BMS_module4Cell1Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell1Volt.can_value();
  msg.buf[5] = BMS_module4Cell1Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell1Volt.can_value();
  msg.buf[7] = BMS_module4Cell1Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_540() {
  static StateCounter ctr;
  msg.id = 540;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell4Volt.can_value();
  msg.buf[3] = BMS_module4Cell4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell5Volt.can_value();
  msg.buf[5] = BMS_module4Cell5Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell6Volt.can_value();
  msg.buf[7] = BMS_module4Cell6Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_541() {
  static StateCounter ctr;
  msg.id = 541;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell7Volt.can_value();
  msg.buf[3] = BMS_module4Cell7Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell8Volt.can_value();
  msg.buf[5] = BMS_module4Cell8Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4cCell9Volt.can_value();
  msg.buf[7] = BMS_module4cCell9Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_542() {
  static StateCounter ctr;
  msg.id = 542;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell10Volt.can_value();
  msg.buf[3] = BMS_module4Cell10Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell11Volt.can_value();
  msg.buf[5] = BMS_module4Cell11Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell12Volt.can_value();
  msg.buf[7] = BMS_module4Cell12Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_543() {
  static StateCounter ctr;
  msg.id = 543;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell13Volt.can_value();
  msg.buf[3] = BMS_module4Cell13Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell14Volt.can_value();
  msg.buf[5] = BMS_module4Cell14Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell15Volt.can_value();
  msg.buf[7] = BMS_module4Cell15Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_544() {
  static StateCounter ctr;
  msg.id = 544;
  msg.len = 8;

  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell16Volt.can_value();
  msg.buf[3] = BMS_module4Cell16Volt.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell17Volt.can_value();
  msg.buf[5] = BMS_module4Cell17Volt.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell18Volt.can_value();
  msg.buf[7] = BMS_module4Cell18Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_545() {
  static StateCounter ctr;
  msg.id = 545;
  msg.len = 8;

 
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell1Temp.can_value();
  msg.buf[3] = BMS_module4Cell1Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell1Temp.can_value();
  msg.buf[5] = BMS_module4Cell1Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell1Temp.can_value();
  msg.buf[7] = BMS_module4Cell1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_546() {
  static StateCounter ctr;
  msg.id = 546;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell4Temp.can_value();
  msg.buf[3] = BMS_module4Cell4Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell5Temp.can_value();
  msg.buf[5] = BMS_module4Cell5Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell6Temp.can_value();
  msg.buf[7] = BMS_module4Cell6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_547() {
  static StateCounter ctr;
  msg.id = 547;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell7Temp.can_value();
  msg.buf[3] = BMS_module4Cell7Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell8Temp.can_value();
  msg.buf[5] = BMS_module4Cell8Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell9Temp.can_value();
  msg.buf[7] = BMS_module4Cell9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_548() {
  static StateCounter ctr;
  msg.id = 548;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell10Temp.can_value();
  msg.buf[3] = BMS_module4Cell10Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell11Temp.can_value();
  msg.buf[5] = BMS_module4Cell11Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell12Temp.can_value();
  msg.buf[7] = BMS_module4Cell12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_549() {
  static StateCounter ctr;
  msg.id = 549;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell13Temp.can_value();
  msg.buf[3] = BMS_module4Cell13Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell14Temp.can_value();
  msg.buf[5] = BMS_module4Cell14Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell15Temp.can_value();
  msg.buf[7] = BMS_module4Cell15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_550() {
  static StateCounter ctr;
  msg.id = 550;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4Cell16Temp.can_value();
  msg.buf[3] = BMS_module4Cell16Temp.can_value() >> 8;
  msg.buf[4] = BMS_module4Cell17Temp.can_value();
  msg.buf[5] = BMS_module4Cell17Temp.can_value() >> 8;
  msg.buf[6] = BMS_module4Cell18Temp.can_value();
  msg.buf[7] = BMS_module4Cell18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_551() {
  static StateCounter ctr;
  msg.id = 551;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell1Volt.can_value();
  msg.buf[3] = BMS_module5Cell1Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell1Volt.can_value();
  msg.buf[5] = BMS_module5Cell1Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell1Volt.can_value();
  msg.buf[7] = BMS_module5Cell1Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_552() {
  static StateCounter ctr;
  msg.id = 552;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell4Volt.can_value();
  msg.buf[3] = BMS_module5Cell4Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell5Volt.can_value();
  msg.buf[5] = BMS_module5Cell5Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell6Volt.can_value();
  msg.buf[7] = BMS_module5Cell6Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_553() {
  static StateCounter ctr;
  msg.id = 553;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell7Volt.can_value();
  msg.buf[3] = BMS_module5Cell7Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell8Volt.can_value();
  msg.buf[5] = BMS_module5Cell8Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell9Volt.can_value();
  msg.buf[7] = BMS_module5Cell9Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_554() {
  static StateCounter ctr;
  msg.id = 554;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell10Volt.can_value();
  msg.buf[3] = BMS_module5Cell10Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell11Volt.can_value();
  msg.buf[5] = BMS_module5Cell11Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell12Volt.can_value();
  msg.buf[7] = BMS_module5Cell12Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_555() {
  static StateCounter ctr;
  msg.id = 555;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell13Volt.can_value();
  msg.buf[3] = BMS_module5Cell13Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell14Volt.can_value();
  msg.buf[5] = BMS_module5Cell14Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell15Volt.can_value();
  msg.buf[7] = BMS_module5Cell15Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_556() {
  static StateCounter ctr;
  msg.id = 556;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell16Volt.can_value();
  msg.buf[3] = BMS_module5Cell16Volt.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell17Volt.can_value();
  msg.buf[5] = BMS_module5Cell17Volt.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell18Volt.can_value();
  msg.buf[7] = BMS_module5Cell18Volt.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_557() {
  static StateCounter ctr;
  msg.id = 557;
  msg.len = 8;

  

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell1Temp.can_value();
  msg.buf[3] = BMS_module5Cell1Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell1Temp.can_value();
  msg.buf[5] = BMS_module5Cell1Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell1Temp.can_value();
  msg.buf[7] = BMS_module5Cell1Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_558() {
  static StateCounter ctr;
  msg.id = 558;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell4Temp.can_value();
  msg.buf[3] = BMS_module5Cell4Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell5Temp.can_value();
  msg.buf[5] = BMS_module5Cell5Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell6Temp.can_value();
  msg.buf[7] = BMS_module5Cell6Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_559() {
  static StateCounter ctr;
  msg.id = 559;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell7Temp.can_value();
  msg.buf[3] = BMS_module5Cell7Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell8Temp.can_value();
  msg.buf[5] = BMS_module5Cell8Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell9Temp.can_value();
  msg.buf[7] = BMS_module5Cell9Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_560() {
  static StateCounter ctr;
  msg.id = 560;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell10Temp.can_value();
  msg.buf[3] = BMS_module5Cell10Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell11Temp.can_value();
  msg.buf[5] = BMS_module5Cell11Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell12Temp.can_value();
  msg.buf[7] = BMS_module5Cell12Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_561() {
  static StateCounter ctr;
  msg.id = 561;
  msg.len = 8;



  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell13Temp.can_value();
  msg.buf[3] = BMS_module5Cell13Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell14Temp.can_value();
  msg.buf[5] = BMS_module5Cell14Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell15Temp.can_value();
  msg.buf[7] = BMS_module5Cell15Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_562() {
  static StateCounter ctr;
  msg.id = 562;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module5Cell16Temp.can_value();
  msg.buf[3] = BMS_module5Cell16Temp.can_value() >> 8;
  msg.buf[4] = BMS_module5Cell17Temp.can_value();
  msg.buf[5] = BMS_module5Cell17Temp.can_value() >> 8;
  msg.buf[6] = BMS_module5Cell18Temp.can_value();
  msg.buf[7] = BMS_module5Cell18Temp.can_value() >> 8;

  can2.write(msg);
}

void send_BMS_563() {
  static StateCounter ctr;
  msg.id = 563;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module1voltageBMSS.can_value();
  msg.buf[3] = BMS_module1voltageBMSS.can_value() >> 8;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_564() {
  static StateCounter ctr;
  msg.id = 564;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module2voltageBMSS.can_value();
  msg.buf[3] = BMS_module2voltageBMSS.can_value() >> 8;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_565() {
  static StateCounter ctr;
  msg.id = 565;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module3voltageBMSS.can_value();
  msg.buf[3] = BMS_module3voltageBMSS.can_value() >> 8;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_566() {
  static StateCounter ctr;
  msg.id = 566;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4voltageBMSS.can_value();
  msg.buf[3] = BMS_module4voltageBMSS.can_value() >> 8;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_BMS_567() {
  static StateCounter ctr;
  msg.id = 567;
  msg.len = 8;


  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_module4voltageBMSS.can_value();
  msg.buf[3] = BMS_module4voltageBMSS.can_value() >> 8;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}



// const int MODULE_2 = 1; // BMS-S select, 1-5

void send_can_2() {

  /*
  static EasyTimer BMS_500_timer(10); // 10Hz for 100ms message interval
  if (BMS_500_timer.isup()) {
    send_BMS_500();
  }

  static EasyTimer BMS_501_timer(10); // 10Hz for 100ms message interval
  if (BMS_501_timer.isup()) {
    send_BMS_501();
  }

  static EasyTimer BMS_502_timer(10); // 10Hz for 100ms message interval
  if (BMS_502_timer.isup()) {
    send_BMS_502();
  }
  */

  switch (MODULE_2) {
    case 1: 
      static EasyTimer BMS_503_timer(10); // 10Hz for 100ms message interval
      if (BMS_503_timer.isup()) {
        send_BMS_503();
      }

      static EasyTimer BMS_504_timer(10); // 10Hz for 100ms message interval
      if (BMS_504_timer.isup()) {
        send_BMS_504();
      }
      static EasyTimer BMS_505_timer(10); // 10Hz for 100ms message interval
      if (BMS_505_timer.isup()) {
        send_BMS_505();
      }

      static EasyTimer BMS_506_timer(10); // 10Hz for 100ms message interval
      if (BMS_506_timer.isup()) {
        send_BMS_506();
      }

      static EasyTimer BMS_507_timer(10); // 10Hz for 100ms message interval
      if (BMS_507_timer.isup()) {
        send_BMS_507();
      }

      static EasyTimer BMS_508_timer(10); // 10Hz for 100ms message interval
      if (BMS_508_timer.isup()) {
        send_BMS_508();
      }

      static EasyTimer BMS_509_timer(10); // 10Hz for 100ms message interval
      if (BMS_509_timer.isup()) {
        send_BMS_509();
      }

      static EasyTimer BMS_510_timer(10); // 10Hz for 100ms message interval
      if (BMS_510_timer.isup()) {
        send_BMS_510();
      }

      static EasyTimer BMS_511_timer(10); // 10Hz for 100ms message interval
      if (BMS_511_timer.isup()) {
        send_BMS_511();
      }

      static EasyTimer BMS_512_timer(10); // 10Hz for 100ms message interval
      if (BMS_512_timer.isup()) {
        send_BMS_512();
      }

      static EasyTimer BMS_513_timer(10); // 10Hz for 100ms message interval
      if (BMS_513_timer.isup()) {
        send_BMS_513();
      }

      static EasyTimer BMS_514_timer(10); // 10Hz for 100ms message interval
      if (BMS_514_timer.isup()) {
        send_BMS_514();
      }

      static EasyTimer BMS_563_timer(10); // 10Hz for 100ms message interval
      if (BMS_563_timer.isup()) {
        send_BMS_563();
      }
      break;

    case 2:
      static EasyTimer BMS_515_timer(10); // 10Hz for 100ms message interval
      if (BMS_515_timer.isup()) {
        send_BMS_515();
      }

      static EasyTimer BMS_516_timer(10); // 10Hz for 100ms message interval
      if (BMS_516_timer.isup()) {
        send_BMS_516();
      }

      static EasyTimer BMS_517_timer(10); // 10Hz for 100ms message interval
      if (BMS_517_timer.isup()) {
        send_BMS_517();
      }

      static EasyTimer BMS_518_timer(10); // 10Hz for 100ms message interval
      if (BMS_518_timer.isup()) {
        send_BMS_518();
      }

      static EasyTimer BMS_519_timer(10); // 10Hz for 100ms message interval
      if (BMS_519_timer.isup()) {
        send_BMS_519();
      }

      static EasyTimer BMS_520_timer(10); // 10Hz for 100ms message interval
      if (BMS_520_timer.isup()) {
        send_BMS_520();
      }

      static EasyTimer BMS_521_timer(10); // 10Hz for 100ms message interval
      if (BMS_521_timer.isup()) {
        send_BMS_521();
      }

      static EasyTimer BMS_522_timer(10); // 10Hz for 100ms message interval
      if (BMS_522_timer.isup()) {
        send_BMS_522();
      }

      static EasyTimer BMS_523_timer(10); // 10Hz for 100ms message interval
      if (BMS_523_timer.isup()) {
        send_BMS_523();
      }

      static EasyTimer BMS_524_timer(10); // 10Hz for 100ms message interval
      if (BMS_524_timer.isup()) {
        send_BMS_524();
      }
      static EasyTimer BMS_525_timer(10); // 10Hz for 100ms message interval
      if (BMS_525_timer.isup()) {
        send_BMS_525();
      }

      static EasyTimer BMS_526_timer(10); // 10Hz for 100ms message interval
      if (BMS_526_timer.isup()) {
        send_BMS_526();
      }

      static EasyTimer BMS_564_timer(10); // 10Hz for 100ms message interval
      if (BMS_564_timer.isup()) {
        send_BMS_564();
      }
      break;
    
    case 3: 
      static EasyTimer BMS_527_timer(10); // 10Hz for 100ms message interval
      if (BMS_527_timer.isup()) {
        send_BMS_527();
      }

      static EasyTimer BMS_528_timer(10); // 10Hz for 100ms message interval
      if (BMS_528_timer.isup()) {
        send_BMS_528();
      }

      static EasyTimer BMS_529_timer(10); // 10Hz for 100ms message interval
      if (BMS_529_timer.isup()) {
        send_BMS_529();
      }

      static EasyTimer BMS_530_timer(10); // 10Hz for 100ms message interval
      if (BMS_530_timer.isup()) {
        send_BMS_530();
      }

      static EasyTimer BMS_531_timer(10); // 10Hz for 100ms message interval
      if (BMS_531_timer.isup()) {
        send_BMS_531();
      }

      static EasyTimer BMS_532_timer(10); // 10Hz for 100ms message interval
      if (BMS_532_timer.isup()) {
        send_BMS_532();
      }

      static EasyTimer BMS_533_timer(10); // 10Hz for 100ms message interval
      if (BMS_533_timer.isup()) {
        send_BMS_533();
      }

      static EasyTimer BMS_534_timer(10); // 10Hz for 100ms message interval
      if (BMS_534_timer.isup()) {
        send_BMS_534();
      }
      static EasyTimer BMS_535_timer(10); // 10Hz for 100ms message interval
      if (BMS_535_timer.isup()) {
        send_BMS_535();
      }

      static EasyTimer BMS_536_timer(10); // 10Hz for 100ms message interval
      if (BMS_536_timer.isup()) {
        send_BMS_536();
      }

      static EasyTimer BMS_537_timer(10); // 10Hz for 100ms message interval
      if (BMS_537_timer.isup()) {
        send_BMS_537();
      }

      static EasyTimer BMS_538_timer(10); // 10Hz for 100ms message interval
      if (BMS_538_timer.isup()) {
        send_BMS_538();
      }
      static EasyTimer BMS_565_timer(10); // 10Hz for 100ms message interval
      if (BMS_565_timer.isup()) {
        send_BMS_565();
      }
      break;

    case 4:
      static EasyTimer BMS_539_timer(10); // 10Hz for 100ms message interval
      if (BMS_539_timer.isup()) {
        send_BMS_539();
      }

      static EasyTimer BMS_540_timer(10); // 10Hz for 100ms message interval
      if (BMS_540_timer.isup()) {
        send_BMS_540();
      }

      static EasyTimer BMS_541_timer(10); // 10Hz for 100ms message interval
      if (BMS_541_timer.isup()) {
        send_BMS_541();
      }

      static EasyTimer BMS_542_timer(10); // 10Hz for 100ms message interval
      if (BMS_542_timer.isup()) {
        send_BMS_542();
      }

      static EasyTimer BMS_543_timer(10); // 10Hz for 100ms message interval
      if (BMS_543_timer.isup()) {
        send_BMS_543();
      }

      static EasyTimer BMS_544_timer(10); // 10Hz for 100ms message interval
      if (BMS_544_timer.isup()) {
        send_BMS_544();
      }
      static EasyTimer BMS_545_timer(10); // 10Hz for 100ms message interval
      if (BMS_545_timer.isup()) {
        send_BMS_545();
      }

      static EasyTimer BMS_546_timer(10); // 10Hz for 100ms message interval
      if (BMS_546_timer.isup()) {
        send_BMS_546();
      }

      static EasyTimer BMS_547_timer(10); // 10Hz for 100ms message interval
      if (BMS_547_timer.isup()) {
        send_BMS_547();
      }

      static EasyTimer BMS_548_timer(10); // 10Hz for 100ms message interval
      if (BMS_548_timer.isup()) {
        send_BMS_548();
      }

      static EasyTimer BMS_549_timer(10); // 10Hz for 100ms message interval
      if (BMS_549_timer.isup()) {
        send_BMS_549();
      }

      static EasyTimer BMS_550_timer(10); // 10Hz for 100ms message interval
      if (BMS_550_timer.isup()) {
        send_BMS_550();
      }
      static EasyTimer BMS_566_timer(10); // 10Hz for 100ms message interval
      if (BMS_566_timer.isup()) {
        send_BMS_566();
      }
      break;

    case 5:
      static EasyTimer BMS_551_timer(10); // 10Hz for 100ms message interval
      if (BMS_551_timer.isup()) {
        send_BMS_551();
      }

      static EasyTimer BMS_552_timer(10); // 10Hz for 100ms message interval
      if (BMS_552_timer.isup()) {
        send_BMS_552();
      }

      static EasyTimer BMS_553_timer(10); // 10Hz for 100ms message interval
      if (BMS_553_timer.isup()) {
        send_BMS_553();
      }

      static EasyTimer BMS_554_timer(10); // 10Hz for 100ms message interval
      if (BMS_554_timer.isup()) {
        send_BMS_554();
      }
      static EasyTimer BMS_555_timer(10); // 10Hz for 100ms message interval
      if (BMS_555_timer.isup()) {
        send_BMS_555();
      }

      static EasyTimer BMS_556_timer(10); // 10Hz for 100ms message interval
      if (BMS_556_timer.isup()) {
        send_BMS_556();
      }

      static EasyTimer BMS_557_timer(10); // 10Hz for 100ms message interval
      if (BMS_557_timer.isup()) {
        send_BMS_557();
      }

      static EasyTimer BMS_558_timer(10); // 10Hz for 100ms message interval
      if (BMS_558_timer.isup()) {
        send_BMS_558();
      }

      static EasyTimer BMS_559_timer(10); // 10Hz for 100ms message interval
      if (BMS_559_timer.isup()) {
        send_BMS_559();
      }

      static EasyTimer BMS_560_timer(10); // 10Hz for 100ms message interval
      if (BMS_560_timer.isup()) {
        send_BMS_560();
      }

      static EasyTimer BMS_561_timer(10); // 10Hz for 100ms message interval
      if (BMS_561_timer.isup()) {
        send_BMS_561();
      }

      static EasyTimer BMS_562_timer(10); // 10Hz for 100ms message interval
      if (BMS_562_timer.isup()) {
        send_BMS_562();
      }

      static EasyTimer BMS_567_timer(10); // 10Hz for 100ms message interval
      if (BMS_567_timer.isup()) {
        send_BMS_567();
      }
      break;
  }
}

#endif 