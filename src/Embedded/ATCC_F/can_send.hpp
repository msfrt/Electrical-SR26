#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"

#include "sensors.hpp"

static CAN_message_t msg;

// accounts for 50% of rotor being slots
float voltage_to_rotor_temp(float voltage){
    return pow((0.5*pow((25+273),4)+0.5*pow((voltage+273),4)), (1/4));
}

float voltage_to_sus_pot_val(float voltage){
  return map(voltage, 0, 5, 0, 150);;
}

/*
// message definitions below
void send_ATCC_300(){
  static StateCounter ctr;

  msg.id = 300;
  msg.len = 8;

  ATCC_boardTemp = 0; //board_temp.value();
  ATCC_teensyTemp = tempmonGetTemp();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_boardTemp.can_value();
  msg.buf[3] = ATCC_boardTemp.can_value() >> 8;
  msg.buf[4] = ATCC_teensyTemp.can_value();
  msg.buf[5] = ATCC_teensyTemp.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1 */

void send_ATCC_301(){
  static StateCounter ctr;

  msg.id = 301;
  msg.len = 8;

  ATCCF_wheelSpeedFR = ATCCF_wheelSpeedFR.value();
  ATCCF_wheelSpeedFL = ATCCF_wheelSpeedFL.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_wheelSpeedFR.can_value();
  msg.buf[3] = ATCCF_wheelSpeedFR.can_value() >> 8;
  msg.buf[4] = ATCCF_wheelSpeedFL.can_value();
  msg.buf[5] = ATCCF_wheelSpeedFL.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

/*
void send_ATCC_302(){
  static StateCounter ctr;

  msg.id = 302;
  msg.len = 8;

  ATCC_angularWheelFreqRL = ATCC_angularWheelFreqFL.value();
  ATCC_angularWheelFreqRR = ATCC_angularWheelFreqFR.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_angularWheelFreqRL.can_value();
  msg.buf[3] = ATCC_angularWheelFreqRL.can_value() >> 8;
  msg.buf[4] = ATCC_angularWheelFreqRR.can_value();
  msg.buf[5] = ATCC_angularWheelFreqRR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1 */

void send_ATCC_304(){
  static StateCounter ctr;
  Serial.println("sendingATCC303");

  msg.id = 305;
  msg.len = 8;

  ATCCF_rotTemp_FL = voltage_to_rotor_temp(RotorTempFL.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempMotorIn.avg());
  ATCCF_rotTemp_FR = voltage_to_rotor_temp(RotorTempFR.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterIn.avg());
  
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
  Serial.println("sendingATCC303");

  msg.id = 305;
  msg.len = 8;

  ATCCF_susPot_FR = voltage_to_sus_pot_val(SusPotFL.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempMotorIn.avg());
  ATCCF_susPot_FL = voltage_to_sus_pot_val(SusPotFR.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterIn.avg());
  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCF_susPot_FR.can_value();
  msg.buf[3] = ATCCF_susPot_FR.can_value() >> 8;
  msg.buf[4] = ATCCF_susPot_FL.can_value();
  msg.buf[5] = ATCCF_susPot_FL.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
}

void send_can1(){

  /*
  static EasyTimer ATCC_300_timer(1); // 200Hz
  if (ATCC_300_timer.isup()){
    send_ATCC_300();
  } */

  static EasyTimer ATCC_301_timer(10); // 10Hz
  if (ATCC_301_timer.isup()){
    send_ATCC_301();
  }

  
  static EasyTimer ATCC_304_timer(10); // 10Hz
  if (ATCC_304_timer.isup()){
    send_ATCC_304();
  }

  static EasyTimer ATCC_305_timer(100); // 100Hz
  if (ATCC_305_timer.isup()){
    send_ATCC_305();
  }

}

#endif
