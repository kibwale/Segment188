#include <Segment188.h>

Segment188 segment(PA0, PA1, PA2, PA3, PA4); // datasheet pins 1,2,3,4,5

void setup() {
  segment.begin();
}

void loop() {
  segment.update();        // call every loop() pass — non-blocking
  segment.setValue(147);   // call whenever the value changes
}
