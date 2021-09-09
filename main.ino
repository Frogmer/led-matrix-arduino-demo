// 引用I2C库
#include <Wire.h>

// 引用ht16k33库
#include "ht16k33.h"

// LED Matrix 模块默认地址为：0x70
#define I2C_ADDR 0x70

HT16K33 *led = NULL;  // 申明模块变量

void setup() {
  // 初始化I2C, 也可以使用TwoWire
  Wire.begin();
  // 初始化串口
  Serial.begin(115200);

  while (led == NULL) {
    // 当led没有实例化，就循环检测模块是否连接
    Wire.beginTransmission(I2C_ADDR);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("LED Matrix module is found at address 0x");
      Serial.println(I2C_ADDR, HEX);
      led = new HT16K33(I2C_ADDR);
    }
    delay(2000);
  }

  // 打开模块
  led->displayOn();
}

void loop() {
  if (led != NULL) {
    // 清除模块所有显示
    led->clear();
    // 每次需要刷新模块显示，都需要调用write方法将数据传递给模块
    led->write();

    // 瀑布demo
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        led->setPixel(i, j, 1);
        led->write();
        delay(50);
      }
    }
  }
  delay(2000);
}