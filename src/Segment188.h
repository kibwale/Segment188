/*
 * Segment188 — driver library for the 188-type (YF2252SR-5) charlieplexed
 * digital Segment, 5 GPIO pins, displays values 0-199.
 *
 * Usage:
 *   #include <Segment188.h>
 *   Segment188 Segment(PA0, PA1, PA2, PA3, PA4); // datasheet pins 1,2,3,4,5
 *
 *   void setup() { Segment.begin(); }
 *   void loop() {
 *     Segment.setValue(147);   // call whenever the value changes
 *     Segment.update();        // call every loop() pass — non-blocking scan
 *   }
 */

#ifndef SEGMENT188_H
#define SEGMENT188_H

#include <Arduino.h>

class Segment188 {
public:
  Segment188(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5);

  void begin();

  // value: 0-199. 0-99 shows just two digits; 100-199 also lights the
  // leading "1" and shows (value-100) as the two digits.
  void setValue(uint16_t value);

  // Call this as often as possible from loop() — it's non-blocking and
  // only actually does work once per stepIntervalUs microseconds.
  void update();

  // Optional: change scan speed. Default is 300us/segment (~208Hz refresh).
  void setStepInterval(unsigned long microseconds);

  // Optional: turn the whole display off.
  void clear();

private:
  enum SegmentId {
    SEG_B1, SEG_C1,
    SEG_A2, SEG_B2, SEG_C2, SEG_D2, SEG_E2, SEG_F2, SEG_G2,
    SEG_A3, SEG_B3, SEG_C3, SEG_D3, SEG_E3, SEG_F3, SEG_G3,
    SEG_COUNT
  };

  struct Segment { uint8_t anode; uint8_t cathode; };

  static const Segment kSegments[SEG_COUNT];
  static const uint8_t kDigitPatterns[10];

  uint8_t pins_[5];
  volatile uint32_t activeMask_;
  uint8_t scanIdx_;
  unsigned long lastStepMicros_;
  unsigned long stepIntervalUs_;

  void setDigits(bool showOne, uint8_t digitTens, uint8_t digitUnits);
  void allPinsHiZ();
  void driveSegment(SegmentId id);
};

#endif
