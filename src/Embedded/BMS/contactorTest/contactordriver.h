#ifndef CONTACTORDRIVER_H_
#define CONTACTORDRIVER_H_

#define DIA_EN1 5
#define DIA_EN2 7
#define EN1_1 3
#define EN1_2 8
#define EN2_1 24
#define EN2_2 2
#define SEL1_2 4
#define SEL1_1 28
#define SEL2 6
#define CNT_CURR 25

void disableAllCont();
void contactorInit();
void enableDischarge();
void disableDischarge();
void enablePrecharge();
void disablePrecharge();
void enableAirPlus();
void disableAirPlus();
void enableAirMinus();
void disableAirMinus();


#endif