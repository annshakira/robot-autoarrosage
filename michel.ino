#include <Wire.h>
#include <ds3231.h>
#include <LiquidCrystal_I2C.h>

struct ts t;

LiquidCrystal_I2C lcd(0x27,20,4);

int pump = 13;
int sensmoist;
int waterThreshold = 650;
int wateringTime = 10000;
int wateringDelay = 30000;
int moistureValue;

void setup() {
  pinMode(pump, OUTPUT);
  lcd.init();
  Wire.begin();
  DS3231_init(DS3231_INTCN);
  lcd.backlight();
}

void loop() {
  sensmoist = analogRead(0);
  DS3231_get(&t);
  lcd.setCursor(0,0);
  if (t.hour < 19) {
    lcd.print("Bonjour, Anne !");
  }
  else {
    lcd.print("Bonsoir, Anne !");
  }
  
  lcd.print(" Il");
  lcd.setCursor(0,1);
  lcd.print("est ");
  lcd.print(t.hour);
  lcd.print("h");
    if (t.min < 10) {
    lcd.print("0");
    lcd.print(t.min);
    }
    else {
  lcd.print(t.min);
    }
  lcd.print(" et je suis");
  
  moistureValue = (-0.22 * sensmoist + 188);
  
  lcd.setCursor(0,2);
  lcd.print(moistureValue);
  lcd.print("% humide. Dernier");
  lcd.setCursor(0,3);
  lcd.print("arrosage : ");
  
  if (sensmoist > waterThreshold) {
    digitalWrite(pump, HIGH);
    delay(wateringTime);
    digitalWrite(pump, LOW);
    lcd.print(t.hour);
    lcd.print("h");
      if (t.min < 10) {
    lcd.print("0");
    lcd.print(t.min);
      }
      else {
    lcd.print(t.min);
      }
    delay(wateringDelay - wateringTime);
  }
  else {
    digitalWrite(pump, LOW);
    delay(wateringDelay);
  }
 
}