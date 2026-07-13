#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "camera_helper.h"

// 板载 NeoPixel RGB LED
#define PIN_PIXS   48   // GPIO48
#define PIX_NUM    1    // 1 颗 LED

Adafruit_NeoPixel pixels(PIX_NUM, PIN_PIXS, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 41, 42); // UART1: RX=GPIO46, TX=GPIO47
  delay(500);
  pixels.begin();
  pixels.clear();
  pixels.show();

  Serial.println("========================================");
  Serial.println("  GOOUUU ESP32-S3-CAM 启动成功！");
  Serial.println("  LED: NeoPixel RGB (GPIO48)");
  Serial.println("========================================");

  // 打印 PSRAM 信息
  if (psramFound()) {
    Serial.printf("PSRAM: 已检测到 (%d KB)\n", ESP.getPsramSize() / 1024);
  } else {
    Serial.println("PSRAM: 未检测到");
  }
  Serial.printf("Free Heap: %d KB\n", ESP.getFreeHeap() / 1024);

  // 初始化摄像头和 SD 卡
  cameraInit();
}

void loop() {
  //// 拍照测试：每 5 秒拍一张
  //String path = capturePhoto();
  //if (path.length() > 0) {
  //  Serial.printf("照片已保存: %s\n", path.c_str());
  //} else {
  //  Serial.println("拍照失败！");
  //}
//
  //// LED 指示：拍照时闪蓝灯
  //pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  //pixels.show();
  //delay(500);
  //pixels.clear();
  //pixels.show();
//
  Serial.println("Hello, RoboTrack!");
  Serial1.println("HHHHello, RoboTrack!");
  delay(500);
}