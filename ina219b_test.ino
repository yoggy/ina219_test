#include <Wire.h>
#include <Adafruit_INA219.h> // see also...https://learn.adafruit.com/adafruit-ina219-current-sensor-breakout/programming

Adafruit_INA219 ina219;

void setup(void)
{
  Serial.begin(115200);
  ina219.begin();
  aqm1602_init();
}

int count = 0;
char buf[16];
char str[16];

void loop(void)
{
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();

  Serial.print(busvoltage);
  Serial.print(",");
  Serial.print(current_mA);
  Serial.println("");

  count ++;
  if (count == 50) {
    memset(str, 0, 16);
    dtostrf(busvoltage, 8, 2, str);
    memset(buf, 0, 16);
    sprintf(buf, "V:%s(V)", str);
    aqm1602_move_cursor(0, 0);
    aqm1602_print(buf);

    memset(str, 0, 16);
    dtostrf(current_mA, 8, 1, str);
    memset(buf, 0, 16);
    sprintf(buf, "I:%s(mA)", str);
    aqm1602_move_cursor(0, 1);
    aqm1602_print(buf);

    count = 0;
  }

  delay(5);
}
