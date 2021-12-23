#include <Wire.h>

#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();
uint16_t maxR, maxG, maxB;

void setup(void) {
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

void loop(void) {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);

  if (r > maxR) {
    maxR = r;
  } else if (g > maxG) {
    maxG = g;
  } else if (b > maxB) {
    maxB = b;
  }

  Serial.print("Max R: ");
  Serial.print(maxR);
  Serial.print("Max G: ");
  Serial.print(maxG);
  Serial.println("Max B: ");
  Serial.print(maxB);
}
