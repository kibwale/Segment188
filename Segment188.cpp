#include "Segment188.h"

// {anode, cathode} pin numbers as printed in the datasheet (1-5).
const Segment188::Segment Segment188::kSegments[SEG_COUNT] = {
  {3, 4}, {2, 4},                                          // B1, C1
  {2, 3}, {3, 2}, {4, 3}, {4, 2}, {5, 2}, {5, 3}, {5, 4},   // A2..G2
  {1, 2}, {2, 1}, {1, 3}, {3, 1}, {1, 4}, {4, 1}, {5, 1},   // A3..G3
};

// Standard 7-segment patterns, bit0=A ... bit6=G, for digits 0-9.
const uint8_t Segment188::kDigitPatterns[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

Segment188::Segment188(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5)
  : activeMask_(0), scanIdx_(0), lastStepMicros_(0), stepIntervalUs_(300) {
  pins_[0] = pin1;
  pins_[1] = pin2;
  pins_[2] = pin3;
  pins_[3] = pin4;
  pins_[4] = pin5;
}

void Segment188::begin() {
  allPinsHiZ();
}

void Segment188::setStepInterval(unsigned long microseconds) {
  stepIntervalUs_ = microseconds;
}

void Segment188::clear() {
  activeMask_ = 0;
}

void Segment188::setValue(uint16_t value) {
  if (value > 199) value = 199;

  bool showOne = value >= 100;
  uint16_t remainder = showOne ? (value - 100) : value;
  uint8_t tens = remainder / 10;
  uint8_t units = remainder % 10;

  setDigits(showOne, tens, units);
}

void Segment188::setDigits(bool showOne, uint8_t digitTens, uint8_t digitUnits) {
  uint32_t mask = 0;
  if (showOne) mask |= (1UL << SEG_B1) | (1UL << SEG_C1);

  uint8_t patTens  = kDigitPatterns[digitTens % 10];
  uint8_t patUnits = kDigitPatterns[digitUnits % 10];

  for (uint8_t b = 0; b < 7; b++) {
    if (patTens  & (1 << b)) mask |= (1UL << (SEG_A2 + b));
    if (patUnits & (1 << b)) mask |= (1UL << (SEG_A3 + b));
  }

  activeMask_ = mask;
}

void Segment188::allPinsHiZ() {
  for (uint8_t i = 0; i < 5; i++) {
    pinMode(pins_[i], INPUT);
  }
}

void Segment188::driveSegment(SegmentId id) {
  allPinsHiZ();
  uint8_t a = kSegments[id].anode - 1;
  uint8_t c = kSegments[id].cathode - 1;

  pinMode(pins_[a], OUTPUT);
  digitalWrite(pins_[a], HIGH);

  pinMode(pins_[c], OUTPUT);
  digitalWrite(pins_[c], LOW);
}

void Segment188::update() {
  unsigned long now = micros();
  if (now - lastStepMicros_ < stepIntervalUs_) return;
  lastStepMicros_ = now;

  if (activeMask_ & (1UL << scanIdx_)) {
    driveSegment((SegmentId)scanIdx_);
  } else {
    allPinsHiZ();
  }

  scanIdx_++;
  if (scanIdx_ >= SEG_COUNT) scanIdx_ = 0;
}
