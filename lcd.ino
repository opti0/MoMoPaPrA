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


void setup() {
  //ustawienie pinu 22 jako wyjscie żeby sterować jasnością ekranu
  pinMode(22, OUTPUT); 
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("18650");
  lcd.setCursor(0, 1);
  lcd.print("capacity tester");
  delay(2500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Maciej Radecki");
  lcd.setCursor(6, 1);
  lcd.print("2022");
   delay(2500);
}

void loop() {
  //brightness();
  smooth_brightness();
  //lcd.clear();
  //lcd.print(analogRead(ADC));  
  /*lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(jasnosc);
  delay(2500);*/
}
