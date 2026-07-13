#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "camera_helper.h"

// 板载 NeoPixel RGB LED
#define PIN_PIXS   48   // GPIO48
#define PIX_NUM    1    // 1 颗 LED

Adafruit_NeoPixel pixels(PIX_NUM, PIN_PIXS, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
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
  static int count = 0;
  Serial.println("Test USB Serial. Count: " + String(count));
  count++;

  // LED 闪烁提示
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // 红色
  pixels.show();

  String photoPath = capturePhoto();
  if (photoPath.length() > 0) {
    Serial.println("拍照成功，保存路径: " + photoPath);
  } else {
    Serial.println("拍照失败！");
  }

  delay(200);



  pixels.clear();
  pixels.show();
  delay(200);
}