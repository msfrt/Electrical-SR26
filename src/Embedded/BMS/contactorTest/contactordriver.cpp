#include "contactordriver.h"
#include <Arduino.h>

void contactorInit(){
  pinMode(DIA_EN1, OUTPUT);
  pinMode(DIA_EN2, OUTPUT);
  pinMode(EN1_1, OUTPUT);
  pinMode(EN1_2, OUTPUT);
  pinMode(EN2_1, OUTPUT);
  pinMode(EN2_2, OUTPUT);
  pinMode(SEL1_2, OUTPUT);
  pinMode(SEL1_1, OUTPUT);
  pinMode(SEL2, OUTPUT);
  pinMode(CNT_CURR, INPUT);
}

void disableAllCont(){
  digitalWrite(EN1_1, LOW);
  digitalWrite(EN2_1, LOW);
  digitalWrite(EN1_2, LOW);
  digitalWrite(EN2_2, LOW);
}

void enableDischarge(){
  //set all enable inputs low
  disableAllCont();
  //set driver 2 EN2 high
  digitalWrite(EN2_2, HIGH);
}

void disableDischarge(){
  digitalWrite(EN2_2, LOW);
}

void enablePrecharge(){
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN2 high
  digitalWrite(EN2_1, HIGH);
}

void disablePrecharge(){
  digitalWrite(EN2_1, LOW);
}

void enableAirPlus(){
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN1 high
  digitalWrite(EN1_1, HIGH);
}

void disableAirPlus(){
  digitalWrite(EN1_1, LOW);
}

void enableAirMinus(){
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN1 high
  digitalWrite(EN1_2, HIGH);
}
void disableAirMinus(){
  digitalWrite(EN1_2, LOW);
}


