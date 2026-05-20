#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"


// external definitions
// extern int OBDFLAG_oil_pressure;
// extern int OBDFLAG_oil_temp;
// extern int OBDFLAG_fuel_pressure;

static CAN_message_t msg;

// send message definitions

void send_PDM_400() {
  static StateCounter ctr;
  msg.id = 400;
  msg.len = 8;

  // PDM_boardTemp = board_temp.value();
  PDM_brakelightVoltAvg = brakelight_volt_sens.avg();
  // PDM_vehichleState = 0; // find sens refrence
  // PDM_coolingOverideActive = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  msg.buf[4] = PDM_brakelightVoltAvg.can_value();
  msg.buf[5] = PDM_brakelightVoltAvg.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  // should have cooling button go direct to PDM in the future I think

  can2.write(msg);
}

void send_PDM_401() {
  static StateCounter ctr;
  msg.id = 401;
  msg.len = 8;

  PDM_pdmCurrentAvg = Imon_ch1.avg();
  PDM_pdmCurrentMax = Imon_ch1.max();
  PDM_pdmCurrentMin = Imon_ch1.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmCurrentMin.can_value();
  msg.buf[3] = PDM_pdmCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmCurrentMax.can_value();
  msg.buf[5] = PDM_pdmCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmCurrentMin.can_value();
  msg.buf[7] = PDM_pdmCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_402() {
  static StateCounter ctr;
  msg.id = 402;
  msg.len = 8;

  PDM_pdmVoltAvg = pdm_volt_sens.avg();
  PDM_pdmVoltMax = pdm_volt_sens.max();
  PDM_pdmVoltMin = pdm_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmVoltAvg.can_value();
  msg.buf[3] = PDM_pdmVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmVoltMax.can_value();
  msg.buf[5] = PDM_pdmVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmVoltMin.can_value();
  msg.buf[7] = PDM_pdmVoltMin.can_value() >> 8;

  can2.write(msg);
}

// void send_PDM_403() {
//   static StateCounter ctr;
//   msg.id = 403;
//   msg.len = 8;
//   PDM_fanRightCurrentAvg = Imon_ch2.avg();
//   PDM_fanRightCurrentMax = Imon_ch2.max();
//   PDM_fanRightCurrentMin = Imon_ch2.min();

//   msg.buf[0] = ctr.value();
//   msg.buf[1] = 0;
//   msg.buf[2] = PDM_fanRightCurrentAvg.can_value();
//   msg.buf[3] = PDM_fanRightCurrentAvg.can_value() >> 8;
//   msg.buf[4] = PDM_fanRightCurrentMax.can_value();
//   msg.buf[5] = PDM_fanRightCurrentMax.can_value() >> 8;
//   msg.buf[6] = PDM_fanRightCurrentMin.can_value();
//   msg.buf[7] = PDM_fanRightCurrentMin.can_value() >> 8;

//   can2.write(msg);
// }

// void send_PDM_404(){
//   static StateCounter ctr;
//   msg.id = 404;
//   msg.len = 8;

//   PDM_fanRightVoltAvg = volt_ch7.avg();
//   PDM_fanRightVoltMax = volt_ch7.max();
//   PDM_fanRightVoltMin = volt_ch7.min();

//   msg.buf[0] = ctr.value();
//   msg.buf[1] = 0;
//   msg.buf[2] = PDM_fanRightVoltAvg.can_value();
//   msg.buf[3] = PDM_fanRightVoltAvg.can_value() >> 8;
//   msg.buf[4] = PDM_fanRightVoltMax.can_value();
//   msg.buf[5] = PDM_fanRightVoltMax.can_value() >> 8;
//   msg.buf[6] = PDM_fanRightVoltMin.can_value();
//   msg.buf[7] = PDM_fanRightVoltMin.can_value() >> 8;

//   can2.write(msg);
// }

void send_PDM_405(){
  static StateCounter ctr;
  msg.id = 405;
  msg.len = 8;

  PDM_fanLeftCurrentAvg = Imon_ch7.avg();
  PDM_fanLeftCurrentMax = Imon_ch7.max();
  PDM_fanLeftCurrentMin = Imon_ch7.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftCurrentAvg.can_value();
  msg.buf[3] = PDM_fanLeftCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanLeftCurrentMax.can_value();
  msg.buf[5] = PDM_fanLeftCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_fanLeftCurrentMin.can_value();
  msg.buf[7] = PDM_fanLeftCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_406(){
  static StateCounter ctr;
  msg.id = 406;
  msg.len = 8;

  PDM_fanLeftVoltAvg = volt_ch7.avg();
  PDM_fanLeftVoltMax = volt_ch7.max();
  PDM_fanLeftVoltMin = volt_ch7.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftVoltAvg.can_value();
  msg.buf[3] = PDM_fanLeftVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanLeftVoltMax.can_value();
  msg.buf[5] = PDM_fanLeftVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_fanLeftVoltMin.can_value();
  msg.buf[7] = PDM_fanLeftVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_407(){
  static StateCounter ctr;
  msg.id = 407;
  msg.len = 8;

  PDM_wpCurrentAvg = Imon_ch2.avg();
  PDM_wpCurrentMax = Imon_ch2.max();
  PDM_wpCurrentMin = Imon_ch2.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_wpCurrentAvg.can_value();
  msg.buf[3] = PDM_wpCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_wpCurrentMax.can_value();
  msg.buf[5] = PDM_wpCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_wpCurrentMin.can_value();
  msg.buf[7] = PDM_wpCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_408(){
  static StateCounter ctr;
  msg.id = 408;
  msg.len = 8;

  PDM_wpVoltAvg = volt_ch2.avg();
  PDM_wpVoltMax = volt_ch2.max();
  PDM_wpVoltMin = volt_ch2.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_wpVoltAvg.can_value();
  msg.buf[3] = PDM_wpVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_wpVoltMax.can_value();
  msg.buf[5] = PDM_wpVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_wpVoltMin.can_value();
  msg.buf[7] = PDM_wpVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_409(){
  static StateCounter ctr;
  msg.id = 409;
  msg.len = 8;

  PDM_fanLeftDutyCycle = fan_left.actual();
  PDM_fanRightDutyCycle = fan_right.actual();
  PDM_wpDutyCycle = water_pump1.actual();
  PDM_teensyTemp = tempmonGetTemp(); // built-in teensy function

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftDutyCycle.can_value();
  msg.buf[3] = PDM_fanRightDutyCycle.can_value();
  msg.buf[4] = PDM_wpDutyCycle.can_value();
  msg.buf[5] = 0;
  msg.buf[6] = PDM_teensyTemp.can_value();
  msg.buf[7] = PDM_teensyTemp.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_410(){
  msg.id = 410;
  msg.len = 8;

  auto time = millis();
  msg.buf[1] = time;
  msg.buf[2] = time >> 8;
  msg.buf[3] = time >> 16;
  msg.buf[4] = time >> 24;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

// void send_PDM_411(){
//   static StateCounter ctr;
//   msg.id = 411;
//   msg.len = 8;

//   PDM_dataVoltAvg = volt_ch4.avg();
//   PDM_dataVoltMax = volt_ch4.max();
//   PDM_dataVoltMin = volt_ch4.min();

//   msg.buf[0] = ctr.value();
//   msg.buf[1] = 0;
//   msg.buf[2] = PDM_dataVoltAvg.can_value();
//   msg.buf[3] = PDM_dataVoltAvg.can_value() >> 8;
//   msg.buf[4] = PDM_dataVoltMax.can_value();
//   msg.buf[5] = PDM_dataVoltMax.can_value() >> 8;
//   msg.buf[6] = PDM_dataVoltMin.can_value();
//   msg.buf[7] = PDM_dataVoltMin.can_value() >> 8;

//   can2.write(msg);
// }

// void send_PDM_412(){
//   static StateCounter ctr;
//   msg.id = 412;
//   msg.len = 8;

//   PDM_keepAliveVoltAvg = volt_ch5.avg();
//   PDM_keepAliveVoltMax = volt_ch5.max();
//   PDM_keepAliveVoltMin = volt_ch5.min();

//   msg.buf[0] = ctr.value();
//   msg.buf[1] = 0;
//   msg.buf[2] = PDM_keepAliveVoltAvg.can_value();
//   msg.buf[3] = PDM_keepAliveVoltAvg.can_value() >> 8;
//   msg.buf[4] = PDM_keepAliveVoltMax.can_value();
//   msg.buf[5] = PDM_keepAliveVoltMax.can_value() >> 8;
//   msg.buf[6] = PDM_keepAliveVoltMin.can_value();
//   msg.buf[7] = PDM_keepAliveVoltMin.can_value() >> 8;

//   can2.write(msg);
// }

void send_can2(){

  
  static EasyTimer PDM_400_timer(10); // 10Hz
  if (PDM_400_timer.isup()){
    send_PDM_400();
  }

  static EasyTimer PDM_401_timer(10); // 10Hz
  if (PDM_401_timer.isup()){
    send_PDM_401();
  }

  static EasyTimer PDM_402_timer(10); // 10Hz
  if (PDM_402_timer.isup()){
    send_PDM_402();
  }

  // static EasyTimer PDM_403_timer(10); // 10Hz
  // if (PDM_403_timer.isup()){
  //   send_PDM_403();
  // }

  // static EasyTimer PDM_404_timer(10); // 10Hz
  // if (PDM_404_timer.isup()){
  //   send_PDM_404();
  // }

  static EasyTimer PDM_405_timer(10); // 10Hz
  if (PDM_405_timer.isup()){
    send_PDM_405();
  }

  static EasyTimer PDM_406_timer(10); // 10Hz
  if (PDM_406_timer.isup()){
    send_PDM_406();
  }

  static EasyTimer PDM_407_timer(10); // 10Hz
  if (PDM_407_timer.isup()){
    send_PDM_407();
  }

  static EasyTimer PDM_408_timer(10); // 10Hz
  if (PDM_408_timer.isup()){
    send_PDM_408();
  }

  static EasyTimer PDM_409_timer(10); // 10Hz
  if (PDM_409_timer.isup()){
    send_PDM_409();
  }

  static EasyTimer PDM_410_timer(10); // 10Hz
  if (PDM_410_timer.isup()){
    send_PDM_410();
  }

  // static EasyTimer PDM_411_timer(10); // 10Hz
  // if (PDM_411_timer.isup()){
  //   send_PDM_411();
  // }

  // static EasyTimer PDM_412_timer(10); // 10Hz
  // if (PDM_412_timer.isup()){
  //   send_PDM_412();
  // }

  // static EasyTimer PDM_413_timer(10); // 10Hz
  // if (PDM_413_timer.isup()){
  //   send_PDM_413();
  // }

}

#endif
