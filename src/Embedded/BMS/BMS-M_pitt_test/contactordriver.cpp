#include "contactordriver.h"
#include <Arduino.h>






void contactorInit(){
  Serial.println("contactorInit");
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
  Serial.println("disableAllCont");
  digitalWrite(EN1_1, LOW);
  digitalWrite(EN2_1, LOW);
  digitalWrite(EN1_2, LOW);
  digitalWrite(EN2_2, LOW);
}

void enableDischarge(){
  Serial.println("enableDischarge");
  //set all enable inputs low
  disableAllCont();
  //set driver 2 EN2 high
  digitalWrite(EN2_2, HIGH);
}

void disableDischarge(){
  Serial.println("disableDischarge");
  digitalWrite(EN2_2, LOW);
}

void enablePrecharge(){
  Serial.println("enablePrecharge");
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN2 high
  digitalWrite(EN2_1, HIGH);
}

void runPrecharge(){
  Serial.println("runPrecharge");
  digitalWrite(EN2_1, HIGH);// precharge
  digitalWrite(EN1_1, LOW);//air+
  digitalWrite(EN1_2, HIGH);//air-
  digitalWrite(EN2_2, HIGH);//discharge
}

void runDischarge(){
  Serial.println("runDischarge");
  digitalWrite(EN2_2, LOW);
  digitalWrite(EN1_1, LOW);
  digitalWrite(EN2_1, LOW);
  digitalWrite(EN1_2, LOW);
}

void runOperational(){
  Serial.println("runOperational");
  digitalWrite(EN2_2, HIGH);
  digitalWrite(EN1_1, HIGH);
  digitalWrite(EN2_1, LOW);
  digitalWrite(EN1_2, HIGH);
}


void disablePrecharge(){
  Serial.println("disablePrecharge");
  digitalWrite(EN2_1, LOW);
}

void enableAirPlus(){
  Serial.println("enableAirPlus");
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN1 high
  digitalWrite(EN1_1, HIGH);
}

void disableAirPlus(){
  Serial.println("disableAirPlus");
  digitalWrite(EN1_1, LOW);
}

void enableAirMinus(){
  Serial.println("enableAirMinus");
  //set all enable inputs low
  disableAllCont();
  //set driver 1 EN1 high
  digitalWrite(EN1_2, HIGH);
}
void disableAirMinus(){
  Serial.println("disableAirMinus");
  digitalWrite(EN1_2, LOW);
}


