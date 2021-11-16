#include "Adafruit_VL53L1X.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
LiquidCrystal_I2C lcd(0x27, 16,2);
void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin();

  
  if(!vl53.begin(0x29, &Wire)) {
    Serial.println("Error");
  }
  if(!vl53.startRanging()) {
    Serial.println("Error");
  }
  vl53.setTimingBudget(50);

  lcd.backlight();
}
void loop() {
  char str[]="Hello, world!             ";
  int distance;
  if(vl53.dataReady()){
    distance = vl53.distance();
    if(distance==-1) {
      Serial.println("Error");
    }
    Serial.print(distance);
    Serial.println(" mm");
    vl53.clearInterrupt();
  }
  lcd.setCursor(15, 0); // set the cursor to column 15, line 0
  
  for (int pos = 0; pos < 26 ; pos++)
  {
    lcd.scrollDisplayLeft(); 
    lcd.print(str[pos]);
    delay(1000); //wait for 1 seconds
  }
  
  lcd.clear();
}
