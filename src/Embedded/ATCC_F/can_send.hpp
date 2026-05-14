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
  // Serial.println("ATCCR_wheelSpeedRL: ");
  // Serial.println(ATCCR_wheelSpeedRL.value());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_wheelSpeedFL.can_value();
  msg.buf[3] = ATCCF_wheelSpeedFL.can_value() >> 8;
  msg.buf[4] = ATCCF_wheelSpeedFR.can_value();
  msg.buf[5] = ATCCF_wheelSpeedFR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
} // can1

void send_ATCC_304(){
  static StateCounter ctr;

  msg.id = 304;
  msg.len = 8;

  ATCCF_rotTemp_FL = RotorTempFL.avg();
  ATCCF_rotTemp_FR = RotorTempFR.avg();

  // Serial.println("RotorTempFR.avg(): ");
  // Serial.println(RotorTempFR.avg());
  // Serial.println(voltage_to_rotor_temp(RotorTempFR.avg()));
  // Serial.println("RotorTempFL.avg(): ");
  // Serial.println(RotorTempFL.avg());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_rotTemp_FL.can_value();
  msg.buf[3] = ATCCF_rotTemp_FL.can_value() >> 8;
  msg.buf[4] = ATCCF_rotTemp_FR.can_value();
  msg.buf[5] = ATCCF_rotTemp_FR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_ATCC_305(){
  static StateCounter ctr;

  // MODIFY TO INCLUDE HEAVE IF INCLUDING HEAVE POT

  msg.id = 305;
  msg.len = 8;

  // ATCCR_susPot_RR = voltage_to_sus_pot_rear_roll_val(SusPotRearRoll.avg());
  ATCCF_susPot_FH = voltage_to_sus_pot_front_heave_val(SusPotFrontHeave.avg());

  // Serial.println("SusPotFrontHeave.avg(): ");
  // Serial.println(SusPotFrontHeave.avg());

  // Serial.println("SusPotRR.avg(): ");
  // Serial.println(SusPotRR.avg());

  // Serial.println(ATCCF_susPot_FH.value());
  // Serial.println(ATCCR_susPot_RR.value());
  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  // msg.buf[2] = ATCCR_susPot_RR.can_value();
  // msg.buf[3] = ATCCR_susPot_RR.can_value() >> 8;
  msg.buf[4] = ATCCF_susPot_FH.can_value();
  msg.buf[5] = ATCCF_susPot_FH.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_can(){

  static EasyTimer ATCC_301_timer(100); // 100 Hz
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
