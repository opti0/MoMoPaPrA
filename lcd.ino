#include <LiquidCrystal.h>
#include <Time.h>
#define ADC 28

const int rs = 21, en = 20, d4 = 19, d5 = 18, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void brightness(){
  int jasnosc;
  analogReadResolution(12);
  jasnosc = (analogRead(ADC)/1024);
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
  analogWrite(22, (analogRead(ADC)/16)-1); 
}

float voltage_measure(){
  float voltage;
  //here will be some code to measure voltage
  voltage = 12.34;
  return voltage;
  }
  
float current_measure(){
  float current;
  //here will be some code to measure current
  current = 15.28;
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
  lcd.print("R:");
 delay(1000);
}

void initialize(){
  lcd.setCursor(3, 0);
  lcd.print("MoMoPaPrA");
  lcd.setCursor(3, 1);
  lcd.print("KxW MR JxK");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("EZO Projekt");
  lcd.setCursor(6, 1);
  lcd.print("2022");
  delay(2000);
  }

void setup() {
  //set PIN 22 as PWM output to control screen brightness
  pinMode(22, OUTPUT); 
  // set screen diamiters
  lcd.begin(16, 2);
  smooth_brightness();
  initialize();
}



void loop() {
  smooth_brightness();
  measurements_display();
}
