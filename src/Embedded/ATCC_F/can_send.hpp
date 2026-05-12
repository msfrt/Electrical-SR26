#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"

#include "sensors.hpp"
#include "wheel_speed.hpp"

static CAN_message_t msg;

void send_ATCC_301(){
  static StateCounter ctr;

  msg.id = 301;
  msg.len = 8;

  // Serial.println("ATCCR_wheelSpeedRR: ");
  // Serial.println(ATCCR_wheelSpeedRR.value());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_wheelSpeedFL.can_value();
  msg.buf[3] = ATCCF_wheelSpeedFL.can_value() >> 8;
  msg.buf[4] = ATCCF_wheelSpeedFR.can_value();
  msg.buf[5] = ATCCF_wheelSpeedFR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

void send_ATCC_304(){
  static StateCounter ctr;

  msg.id = 304;
  msg.len = 8;

  ATCCF_rotTemp_FL = voltage_to_rotor_temp(RotorTempFL.avg());
  ATCCF_rotTemp_FR = voltage_to_rotor_temp(RotorTempFR.avg());

  // Serial.println("RotorTempRR.avg(): ");
  // Serial.println(RotorTempRR.avg());
  // Serial.println(voltage_to_rotor_temp(RotorTempRR.avg()));

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_rotTemp_FL.can_value();
  msg.buf[3] = ATCCF_rotTemp_FL.can_value() >> 8;
  msg.buf[4] = ATCCF_rotTemp_FR.can_value();
  msg.buf[5] = ATCCF_rotTemp_FR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
}

void send_ATCC_305(){
  static StateCounter ctr;

  msg.id = 305;
  msg.len = 8;

  ATCCF_susPot_FL = SusPotFL.avg();
  ATCCF_susPot_FR = SusPotFR.avg();

  // Serial.println("SusPotRL.avg(): ");
  // Serial.println(SusPotRL.avg());

  // Serial.println("SusPotRR.avg(): ");
  // Serial.println(SusPotRR.avg());

  // Serial.println(ATCCR_susPot_RL.value());
  // Serial.println(ATCCR_susPot_RR.value());
  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_susPot_FL.can_value();
  msg.buf[3] = ATCCF_susPot_FL.can_value() >> 8;
  msg.buf[4] = ATCCF_susPot_FR.can_value();
  msg.buf[5] = ATCCF_susPot_FR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
}

void send_can1(){

  static EasyTimer ATCC_301_timer(100); // 1000 Hz
  if (ATCC_301_timer.isup()){
    send_ATCC_301();
  }

  static EasyTimer ATCC_304_timer(100); // 100 Hz
  if (ATCC_304_timer.isup()){
    send_ATCC_304();
  }

  static EasyTimer ATCC_305_timer(100); // 100 Hz
  if (ATCC_305_timer.isup()){
    send_ATCC_305();
  }

}

#endif
