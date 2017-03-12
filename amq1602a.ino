//////////////////////////////////////////////////////////
//
// aqm1602a.ino - http://akizukidenshi.com/catalog/g/gK-08896/
//
// How to use...
//
//   #include <Wire.h>
//
//   void setup() {
//     Wire.begin();
//     aqm1602_init();
//     aqm1602_print("hello world");
//     delay(1000);
//   }
//   void loop() {}
//
#define AQM1602_ADDR 0x3e

void aqm1602_init() {
  // http://maicommon.ciao.jp/ss/Arduino_g/LCD_I2C/index.htm
  aqm1602_cmd(0x38); // function set (0b00111000) (select instruction table=0)
  aqm1602_cmd(0x39); // function set (0b00111001) (select instruction table=1)
  aqm1602_cmd(0x14); // internal OSC freq (is=1, 0b00010100)
  aqm1602_cmd(0x70); // contrast set (is=1, 0b0111xxxx)
  aqm1602_cmd(0x5a); // power/icon/contrast control (is=1, 5V:5a, 3V:0x5e)
  aqm1602_cmd(0x6c); // follower control (is=1, 0x0110xxxx)

  aqm1602_cmd(0x38); // function set (0b00111000) (select instruction table=0)
  aqm1602_cmd(0x0c); // display on/off (display on, cursor off, cursor position off)

  aqm1602_clear();
}

void aqm1602_clear() {
  aqm1602_cmd(0x01);
}

void aqm1602_print(char *str) {
  aqm1602_print(str, strlen(str));
}

void aqm1602_print(char *str, int len) {
  if (str == NULL) {
    aqm1602_clear();
    return;
  }

  if (len == 0) {
    aqm1602_clear();
    return;
  }

  // for AQM1602 display size
  int char_count = len;
  if (char_count > 32) char_count = 32;

  // print character
  for (int i = 0; i < char_count; ++i) {
    aqm1602_char(str[i]);
    if (i  == 15) {
      aqm1602_move_cursor(0, 1);
    }
  }
}

void aqm1602_move_cursor(uint8_t x, uint8_t y) {
  if (y == 0) {
    aqm1602_cmd(0x80 + x);
  }
  else if (y == 1) {
    aqm1602_cmd(0xc0 + x);
  }
}

void aqm1602_cmd(char d) {
  aqm1602_data(0x00, d);
}

void aqm1602_char(char d) {
  aqm1602_data(0x40, d);
}

void aqm1602_data(char c, char d) {
  Wire.beginTransmission(AQM1602_ADDR);
  Wire.write(c);
  Wire.write(d);
  Wire.endTransmission();
  delayMicroseconds(20);
}

