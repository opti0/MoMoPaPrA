//#include <SPI.h>
#include "pico/multicore.h"
#include <LiquidCrystal.h>

#define ADC_LDR 28
#define ADC_VOLT 26
#define ADC_CURR 27

const int rs = 21, en = 20, d4 = 19, d5 = 18, d6 = 16, d7 = 17;
int offset_curr;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void brightness(){
  int jasnosc;
  analogReadResolution(12);
  jasnosc = (analogRead(ADC_LDR)/1024);
  switch (jasnosc){
    case 0:{
      analogWrite(22, 32);
      break;}
    case 1:{
      analogWrite(22, 64);
      break;}
    case 2:{
      analogWrite(22, 128);
      break; } 
    case 3:{
      analogWrite(22, 255);
      break; }}
  }

void smooth_brightness(){
  analogReadResolution(12);
  analogWrite(22, (analogRead(ADC_LDR)/16)-1); 
}

float voltage_measure(){
  //digitalWrite(13, LOW); // Drive CS pin LOW
  float voltage;
  int odczyt = analogRead(ADC_VOLT);
  voltage = (float)odczyt * 0.0053504; //znromalizowany wynik ADC 1/4096*3.3V*6,641 (odwrotna przekładnia)
  if (voltage >20)
    return 0;
  return voltage;
  }
  
float current_measure(){
  
  float current;
  //current = ((analogRead(ADC_CURR)-2048)/4096*3.3*6.6);
  current = (analogRead(ADC_CURR)-offset_curr)*0.00134277;
  return current;
  }

void measurements_display(){
  lcd.clear();
  float power;
  float voltage =  voltage_measure();
  float current = current_measure();
  power = voltage * current;
  lcd.setCursor(1,0);
  lcd.print(voltage);
  lcd.setCursor(6,0);
  lcd.print("V");
  lcd.setCursor(9,0);
  lcd.print("P:");
  lcd.print(int(power));
  lcd.print("W");
  if(current<0)
    lcd.setCursor(0,1);
  else
    lcd.setCursor(1,1);
  lcd.print(current);
  lcd.setCursor(6,1);
  lcd.print("A"); 
  lcd.setCursor(9,1);  
  //lcd.print("R:");
  delay(1000);
}

void initialize(){
  smooth_brightness();
  lcd.setCursor(3, 0);
  lcd.print("MoMoPaPrA");
  lcd.setCursor(3, 1);
  lcd.print("KxW MR JxK");
  offset_curr = analogRead(ADC_CURR);
  delay(2000);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("EZO Projekt");
  lcd.setCursor(6, 1);
  lcd.print("2022");
  delay(2000);
  }

void spiInit() {
  
}

void setup() {
  //set PIN 22 as PWM output to control screen brightness
  pinMode(22, OUTPUT);
  //set SPI pins' direction properly
  pinMode(13, OUTPUT);
  // set screen dimensions
  lcd.begin(16, 2);
  analogReadResolution(12);
  initialize();
}



void loop() {
  smooth_brightness();
  measurements_display();
}
