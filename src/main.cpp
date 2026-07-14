#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "camera_helper.h"

// 板载 NeoPixel RGB LED
#define PIN_PIXS   48   // GPIO48
#define PIX_NUM    1    // 1 颗 LED
#define ViberationInput 42   // GPIO42，振动传感器输入

Adafruit_NeoPixel pixels(PIX_NUM, PIN_PIXS, NEO_GRB + NEO_KHZ800);
volatile int vibrationState;
int count = 0;

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

  pinMode(ViberationInput, INPUT);//浮空输入
}

void loop() {
  // 读取振动传感器状态
  vibrationState = digitalRead(ViberationInput);
  Serial.printf("振动开关状态: %d,计数：%d\n", vibrationState,count);
  count++;
  delay(5);
}



//String photoPath = capturePhoto();
//  if (photoPath.length() > 0) {
//    Serial.println("拍照成功，保存路径: " + photoPath);
//  } else {
//    Serial.println("拍照失败！");
//  }