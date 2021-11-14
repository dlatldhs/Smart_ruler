#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
   
void setup() { 
 lcd.begin(16,2);        // 16열 2행짜리 LCD 사용
 lcd.setCursor(0,0);     // (0,0)위치에 Eduino를 출력
 lcd.print("EDUINO");   
 lcd.setCursor(0,1);     // (0,1)위치에 LCD TEST를 출력
 lcd.print("LCD TEST"); 
}
void loop() {
}
 
