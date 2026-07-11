#include <Arduino.h>
#define LED_PIN 13

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.print("启动成功！Result of myFunction: ");
  Serial.println(result);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}