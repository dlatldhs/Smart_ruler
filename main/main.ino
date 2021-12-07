#include <LiquidCrystal_I2C.h>
#include "Adafruit_VL53L1X.h"
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int piezo = 11;
int count = 0;
int a = 0, b = 0;
void setup() {
  pinMode(4, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(115200);
  Wire.begin();
  if (!vl53.begin(0x29, &Wire)) {
    Serial.println("Error");
  }
  if (!vl53.startRanging()) {
    Serial.println("Error");
  }
  vl53.setTimingBudget(50);
}

void loop() {
  int distance;
  if (vl53.dataReady()) {
    distance = vl53.distance();
    lcd.clear();
    if (distance == -1) {
      lcd.print("error");
    }

    lcd.print((String)distance + "MM  " + (String)(distance / 10.0) + "CM  ");
    lcd.setCursor(0, 1);
    lcd.print((String)(distance / 1000.0) + "M  ");
    count++;
    if (count % 2 != 0) {
      a = 0;
      a = distance;
    }
    if (count % 2 == 0) {
      b = 0;
      b = distance;
    }
    if (a == b) {
      tone(piezo, 784);
      delay(500);
      noTone(piezo);
      lcd.clear();
      lcd.print((String)distance + "MM  " + (String)(distance / 10.0) + "CM  ");
      lcd.setCursor(0, 1);
      lcd.print((String)(distance / 1000.0) + "M  Complete");
      delay(2000);
      a = 0; b = 0;
    }
    vl53.clearInterrupt();
    delay(1000);
  }
}
