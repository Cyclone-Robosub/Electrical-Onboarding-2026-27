#include <Wire.h>
#include <VL53L1X.h>
#include <LiquidCrystal_I2C.h>

VL53L1X sensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int DistanceThreshold = 889; //User set
int prevDistMM = -1; 
void sensor_init(VL53L1X::DistanceMode range_mode, int timing_budget_ms);
void display();

void setup() {
    Wire.begin();

    lcd.init();
    lcd.backlight();
    lcd.clear();

    sensor_init(VL53L1X::Short, 20);
    delay(100);
    sensor.startContinuous(20);

    lcd.setCursor(0,0);
}

void loop() {
    display();
    delay(100);
}

void sensor_init(VL53L1X::DistanceMode range_mode, int timing_budget_ms) {
    sensor.setTimeout(500);
    sensor.init();
    sensor.setDistanceMode(range_mode);
    sensor.setMeasurementTimingBudget(timing_budget_ms * 1000);
}

void display() {
    int currentDistMM = sensor.read()

    if (prevDistMM >= DistanceThreshold && currentDistMM < DistanceThreshold) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Message 2"); //User set
    }

    if (prevDistMM < DistanceThreshold && currentDistMM >= DistanceThreshold && prevDistMM != -1) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Message 1"); //User set
    }

    prevDistMM = currentDistMM;
    }
}
