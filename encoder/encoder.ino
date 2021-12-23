#include <Wire.h>

#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();
uint16_t maxR = 300;
uint16_t maxG = 200;
uint16_t maxB = 100;

uint16_t r, g, b, c;
float scaledR, scaledG, scaledB;
float minVal, maxVal, diff;
float hue, sat, val;

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
    tcs.setInterrupt(1);
  } else {
    Serial.println("Not found");
    while (1)
      ;
  }
}

void loop() {
  tcs.getRawData(&r, &g, &b, &c);
  scaledR = 1.0 * r / maxR;
  scaledG = 1.0 * g / maxG;
  scaledB = 1.0 * b / maxB;

  maxVal = max(max(scaledR, scaledG), scaledB);
  minVal = min(min(scaledR, scaledG), scaledB);
  diff = maxVal - minVal;

  if (maxVal == scaledR) {
    hue = 60.0 * ((int)((scaledG - scaledB) / diff) % 6);
  } else if (maxVal == scaledG) {
    hue = 60.0 * ((scaledB - scaledR) / diff + 2.0);
  } else if (maxVal == scaledB) {
    hue = 60.0 * ((scaledR - scaledG) / diff + 4.0);
  }

  Serial.print("Hue angle: ");
  Serial.println(hue);
}
