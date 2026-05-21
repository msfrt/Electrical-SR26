#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"

#include "sensors.hpp"
#include "wheel_speed.hpp"

static CAN_message_t msg;

void send_ATCC_201(){
  static StateCounter ctr;

  msg.id = 201;
  msg.len = 8;

  // Serial.println("ATCCR_wheelSpeedRR: ");
  // Serial.println(ATCCR_wheelSpeedRR.value());
  // Serial.println("ATCCR_wheelSpeedRL: ");
  // Serial.println(ATCCR_wheelSpeedRL.value());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCR_wheelSpeedRL.can_value();
  msg.buf[3] = ATCCR_wheelSpeedRL.can_value() >> 8;
  msg.buf[4] = ATCCR_wheelSpeedRR.can_value();
  msg.buf[5] = ATCCR_wheelSpeedRR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_ATCC_204(){
  static StateCounter ctr;

  msg.id = 204;
  msg.len = 8;

  ATCCR_rotTemp_RL = RotorTempRL.avg();
  ATCCR_rotTemp_RR = RotorTempRR.avg();

  // Serial.println("RotorTempRR.avg(): ");
  // Serial.println(RotorTempRR.avg());
  // Serial.println(voltage_to_rotor_temp(RotorTempRR.avg()));

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCR_rotTemp_RL.can_value();
  msg.buf[3] = ATCCR_rotTemp_RL.can_value() >> 8;
  msg.buf[4] = ATCCR_rotTemp_RR.can_value();
  msg.buf[5] = ATCCR_rotTemp_RR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_ATCC_208(){
  static StateCounter ctr;

  // MODIFY TO INCLUDE HEAVE IF INCLUDING HEAVE POT

  msg.id = 208;
  msg.len = 8;

  // ATCCR_susPot_RR = voltage_to_sus_pot_rear_roll_val(SusPotRearRoll.avg());
  ATCCR_susPot_RH = voltage_to_sus_pot_rear_heave_val(SusPotRearHeave.avg());

  // Serial.println("SusPotRL.avg(): ");
  // Serial.println(SusPotRL.avg());

  // Serial.println("SusPotRR.avg(): ");
  // Serial.println(SusPotRR.avg());

  // Serial.println(ATCCR_susPot_RL.value());
  // Serial.println(ATCCR_susPot_RR.value());
  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  // msg.buf[2] = ATCCR_susPot_RR.can_value();
  // msg.buf[3] = ATCCR_susPot_RR.can_value() >> 8;
  msg.buf[4] = ATCCR_susPot_RH.can_value();
  msg.buf[5] = ATCCR_susPot_RH.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_can(){

  static EasyTimer ATCC_201_timer(100); // 100 Hz
  if (ATCC_201_timer.isup()){
    send_ATCC_201();
  }

  static EasyTimer ATCC_204_timer(100); // 100 Hz
  if (ATCC_204_timer.isup()){
    send_ATCC_204();
  }

  static EasyTimer ATCC_208_timer(100); // 100 Hz
  if (ATCC_208_timer.isup()){
    send_ATCC_208();
  }

}

#endif
