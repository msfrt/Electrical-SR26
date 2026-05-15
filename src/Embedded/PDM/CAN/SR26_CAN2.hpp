/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <FlexCAN_T4.h>
#include <StateCAN.h>

// Message: ATCCF_300 [0x12c]
StateSignal ATCCF_counterMsg300(4, false, 1, 0.0, 0, 15, 0.0, -1, 300);
StateSignal ATCCF_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 300);
StateSignal ATCCF_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 300);

// Message: ATCCF_301 [0x12d]
StateSignal ATCCF_counterMsg301(4, false, 1, 0.0, 0, 15, 0.0, -1, 301);
StateSignal ATCCF_wheelSpeedFL(16, false, 1, 0.0, 0, 2000, 0.0, -1, 301);
StateSignal ATCCF_wheelSpeedFR(16, false, 1, 0.0, 0, 2000, 0.0, -1, 301);

// Message: ATCCF_302 [0x12e]
StateSignal ATCCF_counterMsg302(4, false, 1, 0.0, 0, 15, 0.0, -1, 302);
StateSignal ATCCF_tireTemp_FLO(16, true, 10, 0.0, 0, 150, 0.0, -1, 302);
StateSignal ATCCF_tireTemp_FLM(16, true, 10, 0.0, 0, 150, 0.0, -1, 302);
StateSignal ATCCF_tireTemp_FLI(16, true, 1, 0.0, 0, 150, 0.0, -1, 302);

// Message: ATCCF_303 [0x12f]
StateSignal ATCCF_counterMsg303(4, false, 1, 0.0, 0, 15, 0.0, -1, 303);
StateSignal ATCCF_tireTemp_FRO(16, true, 10, 0.0, 0, 150, 0.0, -1, 303);
StateSignal ATCCF_tireTemp_FRM(16, true, 10, 0.0, 0, 150, 0.0, -1, 303);
StateSignal ATCCF_tireTemp_FRI(16, true, 1, 0.0, 0, 150, 0.0, -1, 303);

// Message: ATCCF_304 [0x130]
StateSignal ATCCF_counterMsg304(4, false, 1, 0.0, 0, 15, 0.0, -1, 304);
StateSignal ATCCF_rotTemp_FL(16, true, 10, 0.0, 0, 500, 0.0, -1, 304);
StateSignal ATCCF_rotTemp_FR(16, true, 10, 0.0, 0, 500, 0.0, -1, 304);

// Message: ATCCF_305 [0x131]
StateSignal ATCCF_counterMsg305(4, false, 1, 0.0, 0, 15, 0.0, -1, 305);
StateSignal ATCCF_susPot_FR(16, true, 100, 0.0, 0, 500, 0.0, -1, 305);
StateSignal ATCCF_susPot_FH(16, true, 100, 0.0, 0, 500, 0.0, -1, 305);

// Message: ATCCR_200 [0xc8]
StateSignal ATCCR_counterMsg200(4, false, 1, 0.0, 0, 15, 0.0, -1, 200);
StateSignal ATCCR_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 200);
StateSignal ATCCR_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 200);

// Message: ATCCR_201 [0xc9]
StateSignal ATCCR_counterMsg201(4, false, 1, 0.0, 0, 15, 0.0, -1, 201);
StateSignal ATCCR_wheelSpeedRL(16, false, 1, 0.0, 0, 2000, 0.0, -1, 201);
StateSignal ATCCR_wheelSpeedRR(16, false, 1, 0.0, 0, 2000, 0.0, -1, 201);

// Message: ATCCR_202 [0xca]
StateSignal ATCCR_counterMsg202(4, false, 1, 0.0, 0, 15, 0.0, -1, 202);
StateSignal ATCCR_tireTemp_RLO(16, true, 10, 0.0, 0, 150, 0.0, -1, 202);
StateSignal ATCCR_tireTemp_RLM(16, true, 10, 0.0, 0, 150, 0.0, -1, 202);
StateSignal ATCCR_tireTemp_RLI(16, true, 10, 0.0, 0, 150, 0.0, -1, 202);

// Message: ATCCR_203 [0xcb]
StateSignal ATCCR_counterMsg203(4, false, 1, 0.0, 0, 15, 0.0, -1, 203);
StateSignal ATCCR_tireTemp_RRO(16, true, 10, 0.0, 0, 150, 0.0, -1, 203);
StateSignal ATCCR_tireTemp_RRM(16, true, 10, 0.0, 0, 150, 0.0, -1, 203);
StateSignal ATCCR_tireTemp_RRI(16, true, 10, 0.0, 0, 150, 0.0, -1, 203);

// Message: ATCCR_204 [0xcc]
StateSignal ATCCR_counterMsg204(4, false, 1, 0.0, 0, 15, 0.0, -1, 204);
StateSignal ATCCR_rotTemp_RL(16, true, 10, 0.0, 0, 500, 0.0, -1, 204);
StateSignal ATCCR_rotTemp_RR(16, true, 10, 0.0, 0, 500, 0.0, -1, 204);

// Message: ATCCR_205 [0xcd]
StateSignal ATCCR_counterMsg205(4, false, 1, 0.0, 0, 15, 0.0, -1, 205);
StateSignal ATCCR_flowR_Inv_In(16, true, 10, 0.0, 0, 150, 0.0, -1, 205);
StateSignal ATCCR_flowR_Inv_Out(16, true, 10, 0.0, 0, 150, 0.0, -1, 205);

// Message: ATCCR_206 [0xce]
StateSignal ATCCR_counterMsg206(4, false, 1, 0.0, 0, 15, 0.0, -1, 206);
StateSignal ATCCR_coolT_Inv_In(16, true, 10, 0.0, 0, 150, 0.0, -1, 206);
StateSignal ATCCR_coolT_Inv_Out(16, true, 10, 0.0, 0, 150, 0.0, -1, 206);

// Message: ATCCR_207 [0xcf]
StateSignal ATCCR_counterMsg207(4, false, 1, 0.0, 0, 15, 0.0, -1, 207);
StateSignal ATCCR_flowR_Motor_In(16, true, 10, 0.0, 0, 150, 0.0, -1, 207);
StateSignal ATCCR_coolT_Motor_In(16, true, 10, 0.0, 0, 150, 0.0, -1, 207);

// Message: ATCCR_208 [0xd0]
StateSignal ATCCR_counterMsg208(4, false, 1, 0.0, 0, 15, 0.0, -1, 208);
StateSignal ATCCR_susPot_RR(16, true, 100, 0.0, 0, 500, 0.0, -1, 208);
StateSignal ATCCR_susPot_RH(16, true, 100, 0.0, 0, 500, 0.0, -1, 208);

// Message: VCU_150 [0x96]
StateSignal VCU_counterMsg150(4, false, 1, 0.0, 0, 15, 0.0, -1, 150);
StateSignal VCU_throttlePosition(16, true, 10, 0.0, 0, 100, 0.0, -1, 150);
StateSignal VCU_throttlePosition1(16, true, 10, 0.0, 0, 100, 0.0, -1, 150);
StateSignal VCU_throttlePosition2(16, true, 10, 0.0, 0, 100, 0.0, -1, 150);

// Message: VCU_151 [0x97]
StateSignal VCU_counterMsg151(4, false, 1, 0.0, 0, 15, 0.0, -1, 151);
StateSignal VCU_brakeBias(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 151);
StateSignal VCU_brakePressureF(16, true, 10, 0.0, 0, 2000, 0.0, -1, 151);
StateSignal VCU_brakePressureR(16, true, 10, 0.0, 0, 2000, 0.0, -1, 151);

// Message: VCU_152 [0x98]
StateSignal VCU_counterMsg152(4, false, 1, 0.0, 0, 15, 0.0, -1, 152);
StateSignal VCU_vehicleState(8, false, 1, 0.0, 0, 255, 0.0, -1, 152);
StateSignal VCU_tCDial(8, false, 1, 0.0, 0, 255, 0.0, -1, 152);
StateSignal VCU_torqueProfile(8, false, 1, 0.0, 0, 255, 0.0, -1, 152);
StateSignal VCU_torqueCurve(8, false, 1, 0.0, 0, 255, 0.0, -1, 152);
StateSignal VCU_rtmSound(1, false, 1, 0.0, 0, 1, 0.0, -1, 152);

// Message: VCU_153 [0x99]
StateSignal VCU_counterMsg153(4, false, 1, 0.0, 0, 15, 0.0, -1, 153);
StateSignal VCU_startSwitch(1, false, 1, 0.0, 0, 1, 0.0, -1, 153);
StateSignal VCU_pwrUpSwitch(1, false, 1, 0.0, 0, 1, 0.0, -1, 153);
StateSignal VCU_pwrDownSwitch(1, false, 1, 0.0, 0, 1, 0.0, -1, 153);
StateSignal VCU_coolSwitch(1, false, 1, 0.0, 0, 1, 0.0, -1, 153);

// Message: VCU_154 [0x9a]
StateSignal VCU_counterMsg154(4, false, 1, 0.0, 0, 15, 0.0, -1, 154);
StateSignal VCU_tCSensitivity(16, false, 1, 0.0, -20, 3276, 0.0, -1, 154);
StateSignal VCU_tCActive(8, false, 1, 0.0, 0, 255, 0.0, -1, 154);
StateSignal VCU_tCEnable(8, false, 1, 0.0, 0, 255, 0.0, -1, 154);
StateSignal VCU_regenEnable(8, false, 1, 0.0, 0, 255, 0.0, -1, 154);

// Message: VCU_155 [0x9b]
StateSignal VCU_counterMsg155(4, false, 1, 0.0, 0, 15, 0.0, -1, 155);
StateSignal VCU_driveSpeed(16, true, 10, 0.0, -20, 3276, 0.0, -1, 155);
StateSignal VCU_assistedTorque(16, true, 10, 0.0, -300, 300, 0.0, -1, 155);
StateSignal VCU_contactorFault(8, false, 1, 0.0, 0, 255, 0.0, -1, 155);

// Message: VCU_156 [0x9c]
StateSignal VCU_counterMsg156(4, false, 1, 0.0, 0, 15, 0.0, -1, 156);

// Message: BMS_500 [0x1f4]
StateSignal BMS_counterMsg500(8, false, 1, 0.0, 0, 15, 0.0, -1, 500);
StateSignal BMS_packmVoltage(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 500);
StateSignal BMS_packCurrent(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 500);
StateSignal BMS_packSOC(16, false, 1, 0.0, 0, 15, 0.0, -1, 500);

// Message: BMS_501 [0x1f5]
StateSignal BMS_counterMsg501(8, false, 1, 0.0, 0, 15, 0.0, -1, 501);
StateSignal BMS_module1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 501);
StateSignal BMS_module2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 501);
StateSignal BMS_module3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 501);

// Message: BMS_502 [0x1f6]
StateSignal BMS_counterMsg502(8, false, 1, 0.0, 0, 15, 0.0, -1, 502);
StateSignal BMS_module4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 502);
StateSignal BMS_module5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 502);

// Message: BMS_503 [0x1f7]
StateSignal BMS_counterMsg503(8, false, 1, 0.0, 0, 15, 0.0, -1, 503);
StateSignal BMS_module1Cell1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 503);
StateSignal BMS_module1Cell2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 503);
StateSignal BMS_module1Cell3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 503);

// Message: BMS_504 [0x1f8]
StateSignal BMS_counterMsg504(8, false, 1, 0.0, 0, 15, 0.0, -1, 504);
StateSignal BMS_module1Cell4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 504);
StateSignal BMS_module1Cell5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 504);
StateSignal BMS_module1Cell6Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 504);

// Message: BMS_505 [0x1f9]
StateSignal BMS_counterMsg505(8, false, 1, 0.0, 0, 15, 0.0, -1, 505);
StateSignal BMS_module1Cell7Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 505);
StateSignal BMS_module1Cell8Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 505);
StateSignal BMS_module1Cell9Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 505);

// Message: BMS_506 [0x1fa]
StateSignal BMS_counterMsg506(8, false, 1, 0.0, 0, 15, 0.0, -1, 506);
StateSignal BMS_module1Cell10Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 506);
StateSignal BMS_module1Cell11Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 506);
StateSignal BMS_module1Cell12Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 506);

// Message: BMS_507 [0x1fb]
StateSignal BMS_counterMsg507(8, false, 1, 0.0, 0, 15, 0.0, -1, 507);
StateSignal BMS_module1Cell13Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 507);
StateSignal BMS_module1Cell14Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 507);
StateSignal BMS_module1Cell15Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 507);

// Message: BMS_508 [0x1fc]
StateSignal BMS_counterMsg508(8, false, 1, 0.0, 0, 15, 0.0, -1, 508);
StateSignal BMS_module1Cell16Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 508);
StateSignal BMS_module1Cell17Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 508);
StateSignal BMS_module1Cell18Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 508);

// Message: BMS_509 [0x1fd]
StateSignal BMS_counterMsg509(8, false, 1, 0.0, 0, 15, 0.0, -1, 509);
StateSignal BMS_module1Cell1Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 509);
StateSignal BMS_module1Cell2Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 509);
StateSignal BMS_module1Cell3Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 509);

// Message: BMS_510 [0x1fe]
StateSignal BMS_counterMsg510(8, false, 1, 0.0, 0, 15, 0.0, -1, 510);
StateSignal BMS_module1Cell4Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 510);
StateSignal BMS_module1Cell5Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 510);
StateSignal BMS_module1Cell6Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 510);

// Message: BMS_511 [0x1ff]
StateSignal BMS_counterMsg511(8, false, 1, 0.0, 0, 15, 0.0, -1, 511);
StateSignal BMS_module1Cell7Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 511);
StateSignal BMS_module1Cell8Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 511);
StateSignal BMS_module1Cell9Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 511);

// Message: BMS_512 [0x200]
StateSignal BMS_counterMsg512(8, false, 1, 0.0, 0, 15, 0.0, -1, 512);
StateSignal BMS_module1Cell10Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 512);
StateSignal BMS_module1Cell11Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 512);
StateSignal BMS_module1Cell12Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 512);

// Message: BMS_513 [0x201]
StateSignal BMS_counterMsg513(8, false, 1, 0.0, 0, 15, 0.0, -1, 513);
StateSignal BMS_module1Cell13Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 513);
StateSignal BMS_module1Cell14Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 513);
StateSignal BMS_module1Cell15Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 513);

// Message: BMS_514 [0x202]
StateSignal BMS_counterMsg514(8, false, 1, 0.0, 0, 15, 0.0, -1, 514);
StateSignal BMS_module1Cell16Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 514);
StateSignal BMS_module1Cell17Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 514);
StateSignal BMS_module1Cell18Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 514);

// Message: BMS_515 [0x203]
StateSignal BMS_counterMsg515(8, false, 1, 0.0, 0, 15, 0.0, -1, 515);
StateSignal BMS_module2Cell1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 515);
StateSignal BMS_module2Cell2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 515);
StateSignal BMS_module2Cell3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 515);

// Message: BMS_516 [0x204]
StateSignal BMS_counterMsg516(8, false, 1, 0.0, 0, 15, 0.0, -1, 516);
StateSignal BMS_module2Cell4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 516);
StateSignal BMS_module2Cell5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 516);
StateSignal BMS_module2Cell6Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 516);

// Message: BMS_517 [0x205]
StateSignal BMS_counterMsg517(8, false, 1, 0.0, 0, 15, 0.0, -1, 517);
StateSignal BMS_module2Cell7Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 517);
StateSignal BMS_module2Cell8Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 517);
StateSignal BMS_module2Cell9Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 517);

// Message: BMS_518 [0x206]
StateSignal BMS_counterMsg518(8, false, 1, 0.0, 0, 15, 0.0, -1, 518);
StateSignal BMS_module2Cell10Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 518);
StateSignal BMS_module2Cell11Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 518);
StateSignal BMS_module2Cell12Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 518);

// Message: BMS_519 [0x207]
StateSignal BMS_counterMsg519(8, false, 1, 0.0, 0, 15, 0.0, -1, 519);
StateSignal BMS_module2Cell13Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 519);
StateSignal BMS_module2Cell14Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 519);
StateSignal BMS_module2Cell15Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 519);

// Message: BMS_520 [0x208]
StateSignal BMS_counterMsg520(8, false, 1, 0.0, 0, 15, 0.0, -1, 520);
StateSignal BMS_module2Cell16Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 520);
StateSignal BMS_module2Cell17Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 520);
StateSignal BMS_module2Cell18Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 520);

// Message: BMS_521 [0x209]
StateSignal BMS_counterMsg521(8, false, 1, 0.0, 0, 15, 0.0, -1, 521);
StateSignal BMS_module2Cell1Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 521);
StateSignal BMS_module2Cell2Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 521);
StateSignal BMS_module2Cell3Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 521);

// Message: BMS_522 [0x20a]
StateSignal BMS_counterMsg522(8, false, 1, 0.0, 0, 15, 0.0, -1, 522);
StateSignal BMS_module2Cell4Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 522);
StateSignal BMS_module2Cell5Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 522);
StateSignal BMS_module2Cell6Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 522);

// Message: BMS_523 [0x20b]
StateSignal BMS_counterMsg523(8, false, 1, 0.0, 0, 15, 0.0, -1, 523);
StateSignal BMS_module2Cell7Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 523);
StateSignal BMS_module2Cell8Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 523);
StateSignal BMS_module2Cell9Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 523);

// Message: BMS_524 [0x20c]
StateSignal BMS_counterMsg524(8, false, 1, 0.0, 0, 15, 0.0, -1, 524);
StateSignal BMS_module2Cell10Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 524);
StateSignal BMS_module2Cell11Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 524);
StateSignal BMS_module2Cell12Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 524);

// Message: BMS_525 [0x20d]
StateSignal BMS_counterMsg525(8, false, 1, 0.0, 0, 15, 0.0, -1, 525);
StateSignal BMS_Module2Cell13Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 525);
StateSignal BMS_module2Cell14Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 525);
StateSignal BMS_module2Cell15Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 525);

// Message: BMS_526 [0x20e]
StateSignal BMS_counterMsg526(8, false, 1, 0.0, 0, 15, 0.0, -1, 526);
StateSignal BMS_module2Cell16Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 526);
StateSignal BMS_module2Cell17Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 526);
StateSignal BMS_module2Cell18Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 526);

// Message: BMS_527 [0x20f]
StateSignal BMS_counterMsg527(8, false, 1, 0.0, 0, 15, 0.0, -1, 527);
StateSignal BMS_module3Cell1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 527);
StateSignal BMS_module3Cell2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 527);
StateSignal BMS_module3Cell3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 527);

// Message: BMS_528 [0x210]
StateSignal BMS_counterMsg528(8, false, 1, 0.0, 0, 15, 0.0, -1, 528);
StateSignal BMS_module3Cell4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 528);
StateSignal BMS_module3Cell5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 528);
StateSignal BMS_module3Cell6Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 528);

// Message: BMS_529 [0x211]
StateSignal BMS_counterMsg529(8, false, 1, 0.0, 0, 15, 0.0, -1, 529);
StateSignal BMS_module3Cell7Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 529);
StateSignal BMS_module3Cell8Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 529);
StateSignal BMS_module3Cell9Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 529);

// Message: BMS_530 [0x212]
StateSignal BMS_counterMsg530(8, false, 1, 0.0, 0, 15, 0.0, -1, 530);
StateSignal BMS_module3Cell10Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 530);
StateSignal BMS_module3Cell11Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 530);
StateSignal BMS_module3Cell12Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 530);

// Message: BMS_531 [0x213]
StateSignal BMS_counterMsg531(8, false, 1, 0.0, 0, 15, 0.0, -1, 531);
StateSignal BMS_module3Cell13Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 531);
StateSignal BMS_module3Cell14Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 531);
StateSignal BMS_module3Cell15Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 531);

// Message: BMS_532 [0x214]
StateSignal BMS_counterMsg532(8, false, 1, 0.0, 0, 15, 0.0, -1, 532);
StateSignal BMS_module3Cell16Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 532);
StateSignal BMS_module3Cell17Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 532);
StateSignal BMS_module3Cell18Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 532);

// Message: BMS_533 [0x215]
StateSignal BMS_counterMsg533(8, false, 1, 0.0, 0, 15, 0.0, -1, 533);
StateSignal BMS_module3Cell1Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 533);
StateSignal BMS_module3Cell2Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 533);
StateSignal BMS_module3Cell3Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 533);

// Message: BMS_534 [0x216]
StateSignal BMS_counterMsg534(8, false, 1, 0.0, 0, 15, 0.0, -1, 534);
StateSignal BMS_module3Cell4Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 534);
StateSignal BMS_module3Cell5Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 534);
StateSignal BMS_module3Cell6Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 534);

// Message: BMS_535 [0x217]
StateSignal BMS_counterMsg535(8, false, 1, 0.0, 0, 15, 0.0, -1, 535);
StateSignal BMS_module3Cell7Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 535);
StateSignal BMS_module3Cell8Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 535);
StateSignal BMS_module3Cell9Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 535);

// Message: BMS_536 [0x218]
StateSignal BMS_counterMsg536(8, false, 1, 0.0, 0, 15, 0.0, -1, 536);
StateSignal BMS_module3Cell10Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 536);
StateSignal BMS_module3Cell11Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 536);
StateSignal BMS_module3Cell12Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 536);

// Message: BMS_537 [0x219]
StateSignal BMS_counterMsg537(8, false, 1, 0.0, 0, 15, 0.0, -1, 537);
StateSignal BMS_module3Cell13Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 537);
StateSignal BMS_module3Cell14Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 537);
StateSignal BMS_module3Cell15Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 537);

// Message: BMS_538 [0x21a]
StateSignal BMS_counterMsg538(8, false, 1, 0.0, 0, 15, 0.0, -1, 538);
StateSignal BMS_module3Cell16Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 538);
StateSignal BMS_module3Cell17Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 538);
StateSignal BMS_module3Cell18Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 538);

// Message: BMS_539 [0x21b]
StateSignal BMS_counterMsg539(8, false, 1, 0.0, 0, 15, 0.0, -1, 539);
StateSignal BMS_module4Cell1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 539);
StateSignal BMS_module4Cell2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 539);
StateSignal BMS_module4Cell3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 539);

// Message: BMS_540 [0x21c]
StateSignal BMS_counterMsg540(8, false, 1, 0.0, 0, 15, 0.0, -1, 540);
StateSignal BMS_module4Cell4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 540);
StateSignal BMS_module4Cell5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 540);
StateSignal BMS_module4Cell6Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 540);

// Message: BMS_541 [0x21d]
StateSignal BMS_counterMsg541(8, false, 1, 0.0, 0, 15, 0.0, -1, 541);
StateSignal BMS_module4Cell7Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 541);
StateSignal BMS_module4Cell8Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 541);
StateSignal BMS_module4cCell9Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 541);

// Message: BMS_542 [0x21e]
StateSignal BMS_counterMsg542(8, false, 1, 0.0, 0, 15, 0.0, -1, 542);
StateSignal BMS_module4Cell10Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 542);
StateSignal BMS_module4Cell11Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 542);
StateSignal BMS_module4Cell12Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 542);

// Message: BMS_543 [0x21f]
StateSignal BMS_counterMsg543(8, false, 1, 0.0, 0, 15, 0.0, -1, 543);
StateSignal BMS_module4Cell13Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 543);
StateSignal BMS_module4Cell14Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 543);
StateSignal BMS_module4Cell15Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 543);

// Message: BMS_544 [0x220]
StateSignal BMS_counterMsg544(8, false, 1, 0.0, 0, 15, 0.0, -1, 544);
StateSignal BMS_module4Cell16Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 544);
StateSignal BMS_module4Cell17Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 544);
StateSignal BMS_module4Cell18Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 544);

// Message: BMS_545 [0x221]
StateSignal BMS_counterMsg545(8, false, 1, 0.0, 0, 15, 0.0, -1, 545);
StateSignal BMS_module4Cell1Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 545);
StateSignal BMS_module4Cell2Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 545);
StateSignal BMS_module4Cell3Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 545);

// Message: BMS_546 [0x222]
StateSignal BMS_counterMsg546(8, false, 1, 0.0, 0, 15, 0.0, -1, 546);
StateSignal BMS_module4Cell4Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 546);
StateSignal BMS_module4Cell5Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 546);
StateSignal BMS_module4Cell6Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 546);

// Message: BMS_547 [0x223]
StateSignal BMS_counterMsg547(8, false, 1, 0.0, 0, 15, 0.0, -1, 547);
StateSignal BMS_module4Cell7Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 547);
StateSignal BMS_module4Cell8Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 547);
StateSignal BMS_module4Cell9Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 547);

// Message: BMS_548 [0x224]
StateSignal BMS_counterMsg548(8, false, 1, 0.0, 0, 15, 0.0, -1, 548);
StateSignal BMS_module4Cell10Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 548);
StateSignal BMS_module4Cell11Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 548);
StateSignal BMS_module4Cell12Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 548);

// Message: BMS_549 [0x225]
StateSignal BMS_counterMsg549(8, false, 1, 0.0, 0, 15, 0.0, -1, 549);
StateSignal BMS_module4Cell13Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 549);
StateSignal BMS_module4Cell14Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 549);
StateSignal BMS_module4Cell15Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 549);

// Message: BMS_550 [0x226]
StateSignal BMS_counterMsg550(8, false, 1, 0.0, 0, 15, 0.0, -1, 550);
StateSignal BMS_module4Cell16Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 550);
StateSignal BMS_module4Cell17Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 550);
StateSignal BMS_module4Cell18Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 550);

// Message: BMS_551 [0x227]
StateSignal BMS_counterMsg551(8, false, 1, 0.0, 0, 15, 0.0, -1, 551);
StateSignal BMS_module5Cell1Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 551);
StateSignal BMS_module5Cell2Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 551);
StateSignal BMS_module5Cell3Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 551);

// Message: BMS_552 [0x228]
StateSignal BMS_counterMsg552(8, false, 1, 0.0, 0, 15, 0.0, -1, 552);
StateSignal BMS_module5Cell4Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 552);
StateSignal BMS_module5Cell5Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 552);
StateSignal BMS_module5Cell6Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 552);

// Message: BMS_553 [0x229]
StateSignal BMS_counterMsg553(8, false, 1, 0.0, 0, 15, 0.0, -1, 553);
StateSignal BMS_module5Cell7Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 553);
StateSignal BMS_module5Cell8Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 553);
StateSignal BMS_module5Cell9Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 553);

// Message: BMS_554 [0x22a]
StateSignal BMS_counterMsg554(8, false, 1, 0.0, 0, 15, 0.0, -1, 554);
StateSignal BMS_module5Cell10Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 554);
StateSignal BMS_module5Cell11Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 554);
StateSignal BMS_module5Cell12Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 554);

// Message: BMS_555 [0x22b]
StateSignal BMS_counterMsg555(8, false, 1, 0.0, 0, 15, 0.0, -1, 555);
StateSignal BMS_module5Cell13Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 555);
StateSignal BMS_module5Cell14Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 555);
StateSignal BMS_module5Cell15Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 555);

// Message: BMS_556 [0x22c]
StateSignal BMS_counterMsg556(8, false, 1, 0.0, 0, 15, 0.0, -1, 556);
StateSignal BMS_module5Cell16Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 556);
StateSignal BMS_module5Cell17Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 556);
StateSignal BMS_module5Cell18Volt(16, false, 1, 0.0, -3276, 3276, 0.0, -1, 556);

// Message: BMS_557 [0x22d]
StateSignal BMS_counterMsg557(8, false, 1, 0.0, 0, 15, 0.0, -1, 557);
StateSignal BMS_module5Cell1Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 557);
StateSignal BMS_module5Cell2Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 557);
StateSignal BMS_module5Cell3Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 557);

// Message: BMS_558 [0x22e]
StateSignal BMS_counterMsg558(8, false, 1, 0.0, 0, 15, 0.0, -1, 558);
StateSignal BMS_module5Cell4Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 558);
StateSignal BMS_module5Cell5Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 558);
StateSignal BMS_module5Cell6Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 558);

// Message: BMS_559 [0x22f]
StateSignal BMS_counterMsg559(8, false, 1, 0.0, 0, 15, 0.0, -1, 559);
StateSignal BMS_module5Cell7Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 559);
StateSignal BMS_module5Cell8Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 559);
StateSignal BMS_module5Cell9Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 559);

// Message: BMS_560 [0x230]
StateSignal BMS_counterMsg560(8, false, 1, 0.0, 0, 15, 0.0, -1, 560);
StateSignal BMS_module5Cell10Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 560);
StateSignal BMS_module5Cell11Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 560);
StateSignal BMS_module5Cell12Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 560);

// Message: BMS_561 [0x231]
StateSignal BMS_counterMsg561(8, false, 1, 0.0, 0, 15, 0.0, -1, 561);
StateSignal BMS_module5Cell13Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 561);
StateSignal BMS_module5Cell14Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 561);
StateSignal BMS_module5Cell15Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 561);

// Message: BMS_562 [0x232]
StateSignal BMS_counterMsg562(8, false, 1, 0.0, 0, 15, 0.0, -1, 562);
StateSignal BMS_module5Cell16Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 562);
StateSignal BMS_module5Cell17Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 562);
StateSignal BMS_module5Cell18Temp(16, false, 10, 0.0, -3276, 3276, 0.0, -1, 562);

// Message: DD_250 [0xfa]
StateSignal DD_counterMsg250(4, false, 1, 0.0, 0, 15, 0.0, -1, 250);
StateSignal DD_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 250);
StateSignal DD_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 250);

// Message: MM5_372 [0x174]
StateSignal MM5_yawRate(16, false, 200, -163.9, 0, 0, 0.0, -1, 372);
StateSignal MM5_ay(16, false, 7849, -4.1745795, 0, 0, 0.0, -1, 372);

// Message: MM5_376 [0x178]
StateSignal MM5_rollRate(16, false, -200, 163.9, 0, 0, 0.0, -1, 376);
StateSignal MM5_ax(16, false, -7849, 4.1745795, 0, 0, 0.0, -1, 376);

// Message: MM5_380 [0x17c]
StateSignal MM5_az(16, false, -7849, 4.1745795, 0, 0, 0.0, -1, 380);

// Message: MM52_450 [0x1c2]
StateSignal MM52_yawRate(16, false, 200, -163.9, 0, 0, 0.0, -1, 450);
StateSignal MM52_ay(16, false, 7849, -4.1745795, 0, 0, 0.0, -1, 450);

// Message: MM52_451 [0x1c3]
StateSignal MM52_rollRate(16, false, -200, 163.9, 0, 0, 0.0, -1, 451);
StateSignal MM52_ax(16, false, -7849, 4.1745795, 0, 0, 0.0, -1, 451);
StateSignal MM52_az(16, false, -7849, 4.1745795, 0, 0, 0.0, -1, 451);

// Message: PDM_400 [0x190]
StateSignal PDM_counterMsg400(4, false, 1, 0.0, 0, 15, 0.0, -1, 400);
StateSignal PDM_boardTemp(16, true, 10, 0.0, -5, 100, 0.0, -1, 400);
StateSignal PDM_brakelightVoltAvg(16, true, 1000, 0.0, -5, 100, 0.0, -1, 400);
StateSignal PDM_vehicleState(8, true, 1, 0.0, 0, 3, 0.0, -1, 400);
StateSignal PDM_coolingOverrideActive(1, false, 1, 0.0, 0, 0, 0.0, -1, 400);

// Message: PDM_401 [0x191]
StateSignal PDM_counterMsg401(4, false, 1, 0.0, 0, 15, 0.0, -1, 401);
StateSignal PDM_pdmCurrentAvg(16, true, 100, 0.0, -5, 20, 0.0, -1, 401);
StateSignal PDM_pdmCurrentMax(16, true, 100, 0.0, -5, 20, 0.0, -1, 401);
StateSignal PDM_pdmCurrentMin(16, true, 100, 0.0, -5, 20, 0.0, -1, 401);

// Message: PDM_402 [0x192]
StateSignal PDM_counterMsg402(4, false, 1, 0.0, 0, 15, 0.0, -1, 402);
StateSignal PDM_pdmVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 402);
StateSignal PDM_pdmVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 402);
StateSignal PDM_pdmVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 402);

// Message: PDM_403 [0x193]
StateSignal PDM_counterMsg403(4, false, 1, 0.0, 0, 15, 0.0, -1, 403);
StateSignal PDM_fanRightCurrentAvg(16, true, 100, 0.0, -5, 20, 0.0, -1, 403);
StateSignal PDM_fanRightCurrentMax(16, true, 100, 0.0, -5, 20, 0.0, -1, 403);
StateSignal PDM_fanRightCurrentMin(16, true, 100, 0.0, -5, 20, 0.0, -1, 403);

// Message: PDM_404 [0x194]
StateSignal PDM_counterMsg404(4, false, 1, 0.0, 0, 15, 0.0, -1, 404);
StateSignal PDM_fanRightVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 404);
StateSignal PDM_fanRightVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 404);
StateSignal PDM_fanRightVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 404);

// Message: PDM_405 [0x195]
StateSignal PDM_counterMsg405(4, false, 1, 0.0, 0, 15, 0.0, -1, 405);
StateSignal PDM_fanLeftCurrentAvg(16, true, 100, 0.0, -5, 20, 0.0, -1, 405);
StateSignal PDM_fanLeftCurrentMax(16, true, 100, 0.0, -5, 20, 0.0, -1, 405);
StateSignal PDM_fanLeftCurrentMin(16, true, 100, 0.0, -5, 20, 0.0, -1, 405);

// Message: PDM_406 [0x196]
StateSignal PDM_counterMsg406(4, false, 1, 0.0, 0, 15, 0.0, -1, 406);
StateSignal PDM_fanLeftVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 406);
StateSignal PDM_fanLeftVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 406);
StateSignal PDM_fanLeftVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 406);

// Message: PDM_407 [0x197]
StateSignal PDM_counterMsg407(4, false, 1, 0.0, 0, 15, 0.0, -1, 407);
StateSignal PDM_wpCurrentAvg(16, true, 100, 0.0, -5, 20, 0.0, -1, 407);
StateSignal PDM_wpCurrentMax(16, true, 100, 0.0, -5, 20, 0.0, -1, 407);
StateSignal PDM_wpCurrentMin(16, true, 100, 0.0, -5, 20, 0.0, -1, 407);

// Message: PDM_408 [0x198]
StateSignal PDM_counterMsg408(4, false, 1, 0.0, 0, 15, 0.0, -1, 408);
StateSignal PDM_wpVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 408);
StateSignal PDM_wpVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 408);
StateSignal PDM_wpVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 408);

// Message: PDM_409 [0x199]
StateSignal PDM_counterMsg409(4, false, 1, 0.0, 0, 15, 0.0, -1, 409);
StateSignal PDM_fanLeftDutyCycle(8, false, 1, 0.0, 0, 100, 0.0, -1, 409);
StateSignal PDM_fanRightDutyCycle(8, false, 1, 0.0, 0, 100, 0.0, -1, 409);
StateSignal PDM_wpDutyCycle(8, false, 1, 0.0, 0, 100, 0.0, -1, 409);
StateSignal PDM_teensyTemp(16, true, 10, 0.0, -5, 100, 0.0, -1, 409);

// Message: PDM_410 [0x19a]
StateSignal PDM_uptime(32, false, 1, 0.0, 0, 4294967295, 0.0, -1, 410);

// Message: PDM_411 [0x19b]
StateSignal PDM_counterMsg411(4, false, 1, 0.0, 0, 15, 0.0, -1, 411);
StateSignal PDM_glvVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 411);
StateSignal PDM_glvVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 411);
StateSignal PDM_glvVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 411);

// Message: PDM_412 [0x19c]
StateSignal PDM_counterMsg412(4, false, 1, 0.0, 0, 15, 0.0, -1, 412);
StateSignal PDM_dataVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 412);
StateSignal PDM_dataVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 412);
StateSignal PDM_dataVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 412);

// Message: PDM_413 [0x19d]
StateSignal PDM_counterMsg413(4, false, 1, 0.0, 0, 15, 0.0, -1, 413);
StateSignal PDM_keepAliveVoltAvg(16, true, 1000, 0.0, -5, 20, 0.0, -1, 413);
StateSignal PDM_keepAliveVoltMax(16, true, 1000, 0.0, -5, 20, 0.0, -1, 413);
StateSignal PDM_keepAliveVoltMin(16, true, 1000, 0.0, -5, 20, 0.0, -1, 413);

// Message: PDM_414 [0x19e]
StateSignal PDM_counterMsg414(4, false, 1, 0.0, 0, 15, 0.0, -1, 414);
StateSignal PDM_carMiles(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 414);
StateSignal PDM_runtimeHours(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 414);
StateSignal PDM_runtimeMinutes(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 414);




/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/


/*
 * Decode a CAN frame for the message ATCCF_300
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_300(const CAN_message_t &imsg) {

	ATCCF_counterMsg300.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_301
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_301(const CAN_message_t &imsg) {

	ATCCF_counterMsg301.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_wheelSpeedFL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_wheelSpeedFR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_302
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_302(const CAN_message_t &imsg) {

	ATCCF_counterMsg302.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_tireTemp_FLO.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_tireTemp_FLM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_tireTemp_FLI.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_303
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_303(const CAN_message_t &imsg) {

	ATCCF_counterMsg303.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_tireTemp_FRO.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_tireTemp_FRM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_tireTemp_FRI.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_304
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_304(const CAN_message_t &imsg) {

	ATCCF_counterMsg304.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_rotTemp_FL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_rotTemp_FR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_305
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_305(const CAN_message_t &imsg) {

	ATCCF_counterMsg305.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_susPot_FR.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_susPot_FH.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_200
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_200(const CAN_message_t &imsg) {

	ATCCR_counterMsg200.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_201
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_201(const CAN_message_t &imsg) {

	ATCCR_counterMsg201.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_wheelSpeedRL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_wheelSpeedRR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_202
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_202(const CAN_message_t &imsg) {

	ATCCR_counterMsg202.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_tireTemp_RLO.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_tireTemp_RLM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_tireTemp_RLI.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_203
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_203(const CAN_message_t &imsg) {

	ATCCR_counterMsg203.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_tireTemp_RRO.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_tireTemp_RRM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_tireTemp_RRI.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_204
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_204(const CAN_message_t &imsg) {

	ATCCR_counterMsg204.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_rotTemp_RL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_rotTemp_RR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_205
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_205(const CAN_message_t &imsg) {

	ATCCR_counterMsg205.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_flowR_Inv_In.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_flowR_Inv_Out.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_206
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_206(const CAN_message_t &imsg) {

	ATCCR_counterMsg206.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_coolT_Inv_In.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_coolT_Inv_Out.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_207
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_207(const CAN_message_t &imsg) {

	ATCCR_counterMsg207.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_flowR_Motor_In.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_coolT_Motor_In.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_208
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_208(const CAN_message_t &imsg) {

	ATCCR_counterMsg208.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_susPot_RR.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_susPot_RH.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message VCU_150
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_150(const CAN_message_t &imsg) {

	VCU_counterMsg150.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_throttlePosition.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_throttlePosition1.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	VCU_throttlePosition2.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message VCU_151
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_151(const CAN_message_t &imsg) {

	VCU_counterMsg151.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_brakeBias.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_brakePressureF.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	VCU_brakePressureR.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message VCU_152
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_152(const CAN_message_t &imsg) {

	VCU_counterMsg152.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_vehicleState.set_can_value((imsg.buf[1]));
	VCU_tCDial.set_can_value((imsg.buf[2]));
	VCU_torqueProfile.set_can_value((imsg.buf[3]));
	VCU_torqueCurve.set_can_value((imsg.buf[4]));
	VCU_rtmSound.set_can_value(((imsg.buf[5] & 0b00000001)));

}

/*
 * Decode a CAN frame for the message VCU_153
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_153(const CAN_message_t &imsg) {

	VCU_counterMsg153.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_startSwitch.set_can_value(((imsg.buf[1] & 0b00000001)));
	VCU_pwrUpSwitch.set_can_value(((imsg.buf[2] & 0b00000001)));
	VCU_pwrDownSwitch.set_can_value(((imsg.buf[3] & 0b00000001)));
	VCU_coolSwitch.set_can_value(((imsg.buf[4] & 0b00000001)));

}

/*
 * Decode a CAN frame for the message VCU_154
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_154(const CAN_message_t &imsg) {

	VCU_counterMsg154.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_tCSensitivity.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_tCActive.set_can_value((imsg.buf[4]));
	VCU_tCEnable.set_can_value((imsg.buf[5]));
	VCU_regenEnable.set_can_value((imsg.buf[6]));

}

/*
 * Decode a CAN frame for the message VCU_155
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_155(const CAN_message_t &imsg) {

	VCU_counterMsg155.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_driveSpeed.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_assistedTorque.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	VCU_contactorFault.set_can_value((imsg.buf[6]));

}

/*
 * Decode a CAN frame for the message VCU_156
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_156(const CAN_message_t &imsg) {

	VCU_counterMsg156.set_can_value(((imsg.buf[0] & 0b00001111)));

}

/*
 * Decode a CAN frame for the message BMS_500
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_500(const CAN_message_t &imsg) {

	BMS_counterMsg500.set_can_value((imsg.buf[0]));
	BMS_packmVoltage.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_packCurrent.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_packSOC.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_501
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_501(const CAN_message_t &imsg) {

	BMS_counterMsg501.set_can_value((imsg.buf[0]));
	BMS_module1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_502
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_502(const CAN_message_t &imsg) {

	BMS_counterMsg502.set_can_value((imsg.buf[0]));
	BMS_module4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message BMS_503
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_503(const CAN_message_t &imsg) {

	BMS_counterMsg503.set_can_value((imsg.buf[0]));
	BMS_module1Cell1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_504
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_504(const CAN_message_t &imsg) {

	BMS_counterMsg504.set_can_value((imsg.buf[0]));
	BMS_module1Cell4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell6Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_505
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_505(const CAN_message_t &imsg) {

	BMS_counterMsg505.set_can_value((imsg.buf[0]));
	BMS_module1Cell7Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell8Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell9Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_506
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_506(const CAN_message_t &imsg) {

	BMS_counterMsg506.set_can_value((imsg.buf[0]));
	BMS_module1Cell10Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell11Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell12Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_507
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_507(const CAN_message_t &imsg) {

	BMS_counterMsg507.set_can_value((imsg.buf[0]));
	BMS_module1Cell13Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell14Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell15Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_508
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_508(const CAN_message_t &imsg) {

	BMS_counterMsg508.set_can_value((imsg.buf[0]));
	BMS_module1Cell16Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell17Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell18Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_509
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_509(const CAN_message_t &imsg) {

	BMS_counterMsg509.set_can_value((imsg.buf[0]));
	BMS_module1Cell1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_510
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_510(const CAN_message_t &imsg) {

	BMS_counterMsg510.set_can_value((imsg.buf[0]));
	BMS_module1Cell4Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell5Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell6Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_511
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_511(const CAN_message_t &imsg) {

	BMS_counterMsg511.set_can_value((imsg.buf[0]));
	BMS_module1Cell7Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell8Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell9Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_512
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_512(const CAN_message_t &imsg) {

	BMS_counterMsg512.set_can_value((imsg.buf[0]));
	BMS_module1Cell10Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell11Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell12Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_513
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_513(const CAN_message_t &imsg) {

	BMS_counterMsg513.set_can_value((imsg.buf[0]));
	BMS_module1Cell13Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell14Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell15Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_514
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_514(const CAN_message_t &imsg) {

	BMS_counterMsg514.set_can_value((imsg.buf[0]));
	BMS_module1Cell16Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module1Cell17Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module1Cell18Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_515
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_515(const CAN_message_t &imsg) {

	BMS_counterMsg515.set_can_value((imsg.buf[0]));
	BMS_module2Cell1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_516
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_516(const CAN_message_t &imsg) {

	BMS_counterMsg516.set_can_value((imsg.buf[0]));
	BMS_module2Cell4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell6Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_517
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_517(const CAN_message_t &imsg) {

	BMS_counterMsg517.set_can_value((imsg.buf[0]));
	BMS_module2Cell7Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell8Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell9Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_518
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_518(const CAN_message_t &imsg) {

	BMS_counterMsg518.set_can_value((imsg.buf[0]));
	BMS_module2Cell10Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell11Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell12Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_519
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_519(const CAN_message_t &imsg) {

	BMS_counterMsg519.set_can_value((imsg.buf[0]));
	BMS_module2Cell13Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell14Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell15Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_520
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_520(const CAN_message_t &imsg) {

	BMS_counterMsg520.set_can_value((imsg.buf[0]));
	BMS_module2Cell16Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell17Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell18Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_521
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_521(const CAN_message_t &imsg) {

	BMS_counterMsg521.set_can_value((imsg.buf[0]));
	BMS_module2Cell1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_522
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_522(const CAN_message_t &imsg) {

	BMS_counterMsg522.set_can_value((imsg.buf[0]));
	BMS_module2Cell4Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell5Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell6Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_523
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_523(const CAN_message_t &imsg) {

	BMS_counterMsg523.set_can_value((imsg.buf[0]));
	BMS_module2Cell7Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell8Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell9Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_524
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_524(const CAN_message_t &imsg) {

	BMS_counterMsg524.set_can_value((imsg.buf[0]));
	BMS_module2Cell10Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell11Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell12Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_525
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_525(const CAN_message_t &imsg) {

	BMS_counterMsg525.set_can_value((imsg.buf[0]));
	BMS_Module2Cell13Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell14Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell15Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_526
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_526(const CAN_message_t &imsg) {

	BMS_counterMsg526.set_can_value((imsg.buf[0]));
	BMS_module2Cell16Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module2Cell17Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module2Cell18Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_527
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_527(const CAN_message_t &imsg) {

	BMS_counterMsg527.set_can_value((imsg.buf[0]));
	BMS_module3Cell1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_528
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_528(const CAN_message_t &imsg) {

	BMS_counterMsg528.set_can_value((imsg.buf[0]));
	BMS_module3Cell4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell6Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_529
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_529(const CAN_message_t &imsg) {

	BMS_counterMsg529.set_can_value((imsg.buf[0]));
	BMS_module3Cell7Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell8Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell9Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_530
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_530(const CAN_message_t &imsg) {

	BMS_counterMsg530.set_can_value((imsg.buf[0]));
	BMS_module3Cell10Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell11Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell12Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_531
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_531(const CAN_message_t &imsg) {

	BMS_counterMsg531.set_can_value((imsg.buf[0]));
	BMS_module3Cell13Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell14Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell15Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_532
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_532(const CAN_message_t &imsg) {

	BMS_counterMsg532.set_can_value((imsg.buf[0]));
	BMS_module3Cell16Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell17Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell18Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_533
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_533(const CAN_message_t &imsg) {

	BMS_counterMsg533.set_can_value((imsg.buf[0]));
	BMS_module3Cell1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_534
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_534(const CAN_message_t &imsg) {

	BMS_counterMsg534.set_can_value((imsg.buf[0]));
	BMS_module3Cell4Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell5Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell6Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_535
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_535(const CAN_message_t &imsg) {

	BMS_counterMsg535.set_can_value((imsg.buf[0]));
	BMS_module3Cell7Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell8Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell9Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_536
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_536(const CAN_message_t &imsg) {

	BMS_counterMsg536.set_can_value((imsg.buf[0]));
	BMS_module3Cell10Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell11Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell12Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_537
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_537(const CAN_message_t &imsg) {

	BMS_counterMsg537.set_can_value((imsg.buf[0]));
	BMS_module3Cell13Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell14Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell15Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_538
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_538(const CAN_message_t &imsg) {

	BMS_counterMsg538.set_can_value((imsg.buf[0]));
	BMS_module3Cell16Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module3Cell17Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module3Cell18Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_539
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_539(const CAN_message_t &imsg) {

	BMS_counterMsg539.set_can_value((imsg.buf[0]));
	BMS_module4Cell1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_540
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_540(const CAN_message_t &imsg) {

	BMS_counterMsg540.set_can_value((imsg.buf[0]));
	BMS_module4Cell4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell6Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_541
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_541(const CAN_message_t &imsg) {

	BMS_counterMsg541.set_can_value((imsg.buf[0]));
	BMS_module4Cell7Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell8Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4cCell9Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_542
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_542(const CAN_message_t &imsg) {

	BMS_counterMsg542.set_can_value((imsg.buf[0]));
	BMS_module4Cell10Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell11Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell12Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_543
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_543(const CAN_message_t &imsg) {

	BMS_counterMsg543.set_can_value((imsg.buf[0]));
	BMS_module4Cell13Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell14Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell15Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_544
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_544(const CAN_message_t &imsg) {

	BMS_counterMsg544.set_can_value((imsg.buf[0]));
	BMS_module4Cell16Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell17Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell18Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_545
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_545(const CAN_message_t &imsg) {

	BMS_counterMsg545.set_can_value((imsg.buf[0]));
	BMS_module4Cell1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_546
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_546(const CAN_message_t &imsg) {

	BMS_counterMsg546.set_can_value((imsg.buf[0]));
	BMS_module4Cell4Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell5Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell6Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_547
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_547(const CAN_message_t &imsg) {

	BMS_counterMsg547.set_can_value((imsg.buf[0]));
	BMS_module4Cell7Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell8Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell9Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_548
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_548(const CAN_message_t &imsg) {

	BMS_counterMsg548.set_can_value((imsg.buf[0]));
	BMS_module4Cell10Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell11Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell12Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_549
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_549(const CAN_message_t &imsg) {

	BMS_counterMsg549.set_can_value((imsg.buf[0]));
	BMS_module4Cell13Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell14Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell15Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_550
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_550(const CAN_message_t &imsg) {

	BMS_counterMsg550.set_can_value((imsg.buf[0]));
	BMS_module4Cell16Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module4Cell17Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module4Cell18Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_551
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_551(const CAN_message_t &imsg) {

	BMS_counterMsg551.set_can_value((imsg.buf[0]));
	BMS_module5Cell1Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell2Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell3Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_552
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_552(const CAN_message_t &imsg) {

	BMS_counterMsg552.set_can_value((imsg.buf[0]));
	BMS_module5Cell4Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell5Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell6Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_553
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_553(const CAN_message_t &imsg) {

	BMS_counterMsg553.set_can_value((imsg.buf[0]));
	BMS_module5Cell7Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell8Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell9Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_554
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_554(const CAN_message_t &imsg) {

	BMS_counterMsg554.set_can_value((imsg.buf[0]));
	BMS_module5Cell10Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell11Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell12Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_555
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_555(const CAN_message_t &imsg) {

	BMS_counterMsg555.set_can_value((imsg.buf[0]));
	BMS_module5Cell13Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell14Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell15Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_556
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_556(const CAN_message_t &imsg) {

	BMS_counterMsg556.set_can_value((imsg.buf[0]));
	BMS_module5Cell16Volt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell17Volt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell18Volt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_557
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_557(const CAN_message_t &imsg) {

	BMS_counterMsg557.set_can_value((imsg.buf[0]));
	BMS_module5Cell1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_558
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_558(const CAN_message_t &imsg) {

	BMS_counterMsg558.set_can_value((imsg.buf[0]));
	BMS_module5Cell4Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell5Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell6Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_559
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_559(const CAN_message_t &imsg) {

	BMS_counterMsg559.set_can_value((imsg.buf[0]));
	BMS_module5Cell7Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell8Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell9Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_560
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_560(const CAN_message_t &imsg) {

	BMS_counterMsg560.set_can_value((imsg.buf[0]));
	BMS_module5Cell10Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell11Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell12Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_561
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_561(const CAN_message_t &imsg) {

	BMS_counterMsg561.set_can_value((imsg.buf[0]));
	BMS_module5Cell13Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell14Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell15Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message BMS_562
 * \param imsg A reference to the incoming CAN message frame
 */
void read_BMS_562(const CAN_message_t &imsg) {

	BMS_counterMsg562.set_can_value((imsg.buf[0]));
	BMS_module5Cell16Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	BMS_module5Cell17Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	BMS_module5Cell18Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message DD_250
 * \param imsg A reference to the incoming CAN message frame
 */
void read_DD_250(const CAN_message_t &imsg) {

	DD_counterMsg250.set_can_value(((imsg.buf[0] & 0b00001111)));
	DD_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	DD_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message MM5_372
 * \param imsg A reference to the incoming CAN message frame
 */
void read_MM5_372(const CAN_message_t &imsg) {

	MM5_yawRate.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	MM5_ay.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message MM5_376
 * \param imsg A reference to the incoming CAN message frame
 */
void read_MM5_376(const CAN_message_t &imsg) {

	MM5_rollRate.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	MM5_ax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message MM5_380
 * \param imsg A reference to the incoming CAN message frame
 */
void read_MM5_380(const CAN_message_t &imsg) {

	MM5_az.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message MM52_450
 * \param imsg A reference to the incoming CAN message frame
 */
void read_MM52_450(const CAN_message_t &imsg) {

	MM52_yawRate.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	MM52_ay.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message MM52_451
 * \param imsg A reference to the incoming CAN message frame
 */
void read_MM52_451(const CAN_message_t &imsg) {

	MM52_rollRate.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	MM52_ax.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	MM52_az.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message PDM_400
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_400(const CAN_message_t &imsg) {

	PDM_counterMsg400.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_brakelightVoltAvg.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_vehicleState.set_can_value((imsg.buf[6]));
	PDM_coolingOverrideActive.set_can_value(((imsg.buf[7] & 0b00000001)));

}

/*
 * Decode a CAN frame for the message PDM_401
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_401(const CAN_message_t &imsg) {

	PDM_counterMsg401.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_pdmCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_pdmCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_pdmCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_402
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_402(const CAN_message_t &imsg) {

	PDM_counterMsg402.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_pdmVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_pdmVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_pdmVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_403
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_403(const CAN_message_t &imsg) {

	PDM_counterMsg403.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanRightCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanRightCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanRightCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_404
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_404(const CAN_message_t &imsg) {

	PDM_counterMsg404.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanRightVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanRightVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanRightVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_405
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_405(const CAN_message_t &imsg) {

	PDM_counterMsg405.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanLeftCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanLeftCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_406
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_406(const CAN_message_t &imsg) {

	PDM_counterMsg406.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanLeftVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanLeftVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_407
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_407(const CAN_message_t &imsg) {

	PDM_counterMsg407.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_wpCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_wpCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_wpCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_408
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_408(const CAN_message_t &imsg) {

	PDM_counterMsg408.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_wpVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_wpVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_wpVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_409
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_409(const CAN_message_t &imsg) {

	PDM_counterMsg409.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftDutyCycle.set_can_value((imsg.buf[2]));
	PDM_fanRightDutyCycle.set_can_value((imsg.buf[3]));
	PDM_wpDutyCycle.set_can_value((imsg.buf[4]));
	PDM_teensyTemp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_410
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_410(const CAN_message_t &imsg) {

	PDM_uptime.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));

}

/*
 * Decode a CAN frame for the message PDM_411
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_411(const CAN_message_t &imsg) {

	PDM_counterMsg411.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_glvVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_glvVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_glvVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_412
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_412(const CAN_message_t &imsg) {

	PDM_counterMsg412.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_dataVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_dataVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_dataVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_413
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_413(const CAN_message_t &imsg) {

	PDM_counterMsg413.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_keepAliveVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_keepAliveVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_keepAliveVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_414
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_414(const CAN_message_t &imsg) {

	PDM_counterMsg414.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_carMiles.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_runtimeHours.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_runtimeMinutes.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}




/************************************************************************************

    Distribute incoming messages to the correct decoding functions

************************************************************************************/


/*
 * Decode a CAN message for the bus captured in SR26_CAN2.dbc.
 * To more efficiently allocate microcontroller resources, simply comment
 * out unnecessary messages that do not need to be decoded.
 * \param imsg A reference to the incoming CAN frame
 */
void decode_SR26_CAN2(const CAN_message_t &imsg) {

	switch (imsg.id) {

		case 300:
			read_ATCCF_300(imsg);
			break;

		case 301:
			read_ATCCF_301(imsg);
			break;

		case 302:
			read_ATCCF_302(imsg);
			break;

		case 303:
			read_ATCCF_303(imsg);
			break;

		case 304:
			read_ATCCF_304(imsg);
			break;

		case 305:
			read_ATCCF_305(imsg);
			break;

		case 200:
			read_ATCCR_200(imsg);
			break;

		case 201:
			read_ATCCR_201(imsg);
			break;

		case 202:
			read_ATCCR_202(imsg);
			break;

		case 203:
			read_ATCCR_203(imsg);
			break;

		case 204:
			read_ATCCR_204(imsg);
			break;

		case 205:
			read_ATCCR_205(imsg);
			break;

		case 206:
			read_ATCCR_206(imsg);
			break;

		case 207:
			read_ATCCR_207(imsg);
			break;

		case 208:
			read_ATCCR_208(imsg);
			break;

		case 150:
			read_VCU_150(imsg);
			break;

		case 151:
			read_VCU_151(imsg);
			break;

		case 152:
			read_VCU_152(imsg);
			break;

		case 153:
			read_VCU_153(imsg);
			break;

		case 154:
			read_VCU_154(imsg);
			break;

		case 155:
			read_VCU_155(imsg);
			break;

		case 156:
			read_VCU_156(imsg);
			break;

		case 500:
			read_BMS_500(imsg);
			break;

		case 501:
			read_BMS_501(imsg);
			break;

		case 502:
			read_BMS_502(imsg);
			break;

		case 503:
			read_BMS_503(imsg);
			break;

		case 504:
			read_BMS_504(imsg);
			break;

		case 505:
			read_BMS_505(imsg);
			break;

		case 506:
			read_BMS_506(imsg);
			break;

		case 507:
			read_BMS_507(imsg);
			break;

		case 508:
			read_BMS_508(imsg);
			break;

		case 509:
			read_BMS_509(imsg);
			break;

		case 510:
			read_BMS_510(imsg);
			break;

		case 511:
			read_BMS_511(imsg);
			break;

		case 512:
			read_BMS_512(imsg);
			break;

		case 513:
			read_BMS_513(imsg);
			break;

		case 514:
			read_BMS_514(imsg);
			break;

		case 515:
			read_BMS_515(imsg);
			break;

		case 516:
			read_BMS_516(imsg);
			break;

		case 517:
			read_BMS_517(imsg);
			break;

		case 518:
			read_BMS_518(imsg);
			break;

		case 519:
			read_BMS_519(imsg);
			break;

		case 520:
			read_BMS_520(imsg);
			break;

		case 521:
			read_BMS_521(imsg);
			break;

		case 522:
			read_BMS_522(imsg);
			break;

		case 523:
			read_BMS_523(imsg);
			break;

		case 524:
			read_BMS_524(imsg);
			break;

		case 525:
			read_BMS_525(imsg);
			break;

		case 526:
			read_BMS_526(imsg);
			break;

		case 527:
			read_BMS_527(imsg);
			break;

		case 528:
			read_BMS_528(imsg);
			break;

		case 529:
			read_BMS_529(imsg);
			break;

		case 530:
			read_BMS_530(imsg);
			break;

		case 531:
			read_BMS_531(imsg);
			break;

		case 532:
			read_BMS_532(imsg);
			break;

		case 533:
			read_BMS_533(imsg);
			break;

		case 534:
			read_BMS_534(imsg);
			break;

		case 535:
			read_BMS_535(imsg);
			break;

		case 536:
			read_BMS_536(imsg);
			break;

		case 537:
			read_BMS_537(imsg);
			break;

		case 538:
			read_BMS_538(imsg);
			break;

		case 539:
			read_BMS_539(imsg);
			break;

		case 540:
			read_BMS_540(imsg);
			break;

		case 541:
			read_BMS_541(imsg);
			break;

		case 542:
			read_BMS_542(imsg);
			break;

		case 543:
			read_BMS_543(imsg);
			break;

		case 544:
			read_BMS_544(imsg);
			break;

		case 545:
			read_BMS_545(imsg);
			break;

		case 546:
			read_BMS_546(imsg);
			break;

		case 547:
			read_BMS_547(imsg);
			break;

		case 548:
			read_BMS_548(imsg);
			break;

		case 549:
			read_BMS_549(imsg);
			break;

		case 550:
			read_BMS_550(imsg);
			break;

		case 551:
			read_BMS_551(imsg);
			break;

		case 552:
			read_BMS_552(imsg);
			break;

		case 553:
			read_BMS_553(imsg);
			break;

		case 554:
			read_BMS_554(imsg);
			break;

		case 555:
			read_BMS_555(imsg);
			break;

		case 556:
			read_BMS_556(imsg);
			break;

		case 557:
			read_BMS_557(imsg);
			break;

		case 558:
			read_BMS_558(imsg);
			break;

		case 559:
			read_BMS_559(imsg);
			break;

		case 560:
			read_BMS_560(imsg);
			break;

		case 561:
			read_BMS_561(imsg);
			break;

		case 562:
			read_BMS_562(imsg);
			break;

		case 250:
			read_DD_250(imsg);
			break;

		case 372:
			read_MM5_372(imsg);
			break;

		case 376:
			read_MM5_376(imsg);
			break;

		case 380:
			read_MM5_380(imsg);
			break;

		case 450:
			read_MM52_450(imsg);
			break;

		case 451:
			read_MM52_451(imsg);
			break;

		case 400:
			read_PDM_400(imsg);
			break;

		case 401:
			read_PDM_401(imsg);
			break;

		case 402:
			read_PDM_402(imsg);
			break;

		case 403:
			read_PDM_403(imsg);
			break;

		case 404:
			read_PDM_404(imsg);
			break;

		case 405:
			read_PDM_405(imsg);
			break;

		case 406:
			read_PDM_406(imsg);
			break;

		case 407:
			read_PDM_407(imsg);
			break;

		case 408:
			read_PDM_408(imsg);
			break;

		case 409:
			read_PDM_409(imsg);
			break;

		case 410:
			read_PDM_410(imsg);
			break;

		case 411:
			read_PDM_411(imsg);
			break;

		case 412:
			read_PDM_412(imsg);
			break;

		case 413:
			read_PDM_413(imsg);
			break;

		case 414:
			read_PDM_414(imsg);
			break;

	}
}


#endif
