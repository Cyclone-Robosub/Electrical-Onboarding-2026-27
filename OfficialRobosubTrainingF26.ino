#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ultrasonic = 0;
const int DistanceThreshold = 15; //User set


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

LiquidCrystal_I2C lcd(0x27,16, 2); 

void setup()
{
  lcd.init();             
  lcd.backlight();
  Serial.begin(9600);
}


void loop()
{
  ultrasonic = 0.01723 * readUltrasonicDistance(9,10);
  Serial.println(ultrasonic);
  if (ultrasonic >= DistanceThreshold){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Too far!!"); //User set
    lcd.setCursor(0,1);
    lcd.print(ultrasonic);
    delay(1000);
  }

  if (ultrasonic < DistanceThreshold){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Too close!!"); //User set
    lcd.setCursor(0,1);
    lcd.print(ultrasonic);
    delay(1000);
  }
}