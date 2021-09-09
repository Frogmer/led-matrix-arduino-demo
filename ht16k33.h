#ifndef HT16K33_H_
#define HT16K33_H_

#include <Wire.h>

class HT16K33 {
 private:
  uint16_t *_buffer;
  uint8_t _address;
  uint8_t _brightness;

 public:
  enum class Cmd {
    on = 0x21,
    standby = 0x20,
    displayOn = 0x81,
    displayOff = 0x80,
    brightness = 0xE0
  };

  HT16K33(const uint8_t address);
  void writeCmd(uint8_t cmd);
  void writeCmd(Cmd cmd);
  void setBrightness(uint8_t val);
  void displayOn();
  void displayOff();
  void clear();
  void writeRow(uint8_t row);
  void write();
  void setPixel(uint8_t col, uint8_t row, uint8_t val);
};

#endif