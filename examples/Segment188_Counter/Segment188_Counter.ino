// Example: counts 0-199 on the segmented display, one step per second.
#include "Segment188.h"

Segment188 Segment(PA0, PA1, PA2, PA3, PA4); // datasheet pins 1,2,3,4,5 , adjust according to mcu board

uint16_t counter = 0;
unsigned long lastCountUpdate = 0;

void setup() {
  Segment.begin();
}

void loop() {
  Segment.update(); // must be called every loop pass — non-blocking

  if (millis() - lastCountUpdate >= 1000) {
    lastCountUpdate = millis();
    Segment.setValue(counter);
    counter = (counter + 1) % 200; // wraps 0-199
  }
}
