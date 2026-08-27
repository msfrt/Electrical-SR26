#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>

static CAN_message_t msg;

//charging message
void send_BMS_1806E5F4() {

  msg.id = 403105268;
  msg.flags.extended = 1;
  msg.len = 8;

  msg.buf[0] = 0x0E; // max accumulator voltage (V)
  msg.buf[1] = 0x10; // 0x0EC4 is 378V, 0E10 is 360V
  msg.buf[2] = 0x00; // charging current limit (A)
  msg.buf[3] = 0x64; // 0x0064 is 10A
  msg.buf[4] = 0x00;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;

  can3.write(msg);
  // Serial.println("Sent charging message");
}

void send_BMS_500() {
  static StateCounter ctr;
  msg.id = 500;
  msg.len = 8;

  BMS_packCurrent = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = BMS_packmVoltage.can_value();
  msg.buf[3] = BMS_packmVoltage.can_value() >> 8;
  msg.buf[4] = BMS_packCurrent.can_value();
  msg.buf[5] = BMS_packCurrent.can_value() >> 8;
  msg.buf[6] = BMS_packSOC.can_value();
  msg.buf[7] = BMS_packSOC.can_value() >> 8;

  Serial.println("Sent BMS message");
  Serial.println(BMS_packSOC.can_value());
  can2.write(msg);
}

// send message definitions

void send_can2(){

  static EasyTimer BMS_500_timer(10); // 10Hz
  if (BMS_500_timer.isup()){
    send_BMS_500();
  }

}

void send_can3(){

  static EasyTimer BMS_1806E5F4_timer(2); // 2Hz, 500ms
  if (BMS_1806E5F4_timer.isup()){
    send_BMS_1806E5F4();
  }

}

#endif
