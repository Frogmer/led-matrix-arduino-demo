#include "ht16k33.h"

HT16K33::HT16K33(const uint8_t address) {
  _address = address;
  _buffer = (uint16_t*)calloc(8, sizeof(uint16_t));
}

void HT16K33::setBrightness(uint8_t val) {
  if (val == _brightness) {
    return;
  }
  _brightness = val;
  if (_brightness > 0x0F) {
    _brightness = 0x0F;
  }
  writeCmd((uint8_t)Cmd::brightness | _brightness);
}

void HT16K33::writeCmd(Cmd cmd) { writeCmd((uint8_t)cmd); }

void HT16K33::writeCmd(uint8_t cmd) {
  Wire.beginTransmission(_address);
  Wire.write(cmd);
  Wire.endTransmission();
}

void HT16K33::writeRow(uint8_t row) {
  uint16_t out = _buffer[row];
  Wire.write(out & 0xFF);  // first byte
  Wire.write(out >> 8);    // second byte
}
void HT16K33::write() {
  Wire.beginTransmission(_address);
  Wire.write(0x00);

  for (uint8_t row = 0; row < 8; row++) {
    writeRow(row);
  }

  Wire.endTransmission();
}

void HT16K33::displayOn() {
  writeCmd(Cmd::on);
  writeCmd(Cmd::displayOn);
  setBrightness(_brightness);
}

void HT16K33::displayOff() {
  writeCmd(Cmd::displayOff);
  writeCmd(Cmd::standby);
}

void HT16K33::clear() {
  for (uint8_t i = 0; i < 8; i++) {
    _buffer[i] = 0;
  }
}

void HT16K33::setPixel(uint8_t col, uint8_t row, uint8_t val) {
  // bounds checking
  col = col & 0x0F;
  row = row & 0x07;
  val = val & 0x01;

  // write the buffer
  if (val == 1) {
    _buffer[row] |= 1 << col;
  } else {
    _buffer[row] &= ~(1 << col);
  }
}