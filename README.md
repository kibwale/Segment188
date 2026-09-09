# Segment188

Arduino library for driving the 188-type charlieplexed LED digital tube
(e.g. YF2252SR-5) — the "1.88"-style indicator used in TWS earphone
charging boxes and similar projects. Displays values 0–199 using 5 GPIO
pins and no extra driver hardware.

![Wiring diagram](images/wiring.svg)

## Wiring

- 5 GPIO pins → tube pins 1–5, each through its own series resistor
  (start at 100Ω, tune for brightness — 1 resistor per pin, not per LED).
- No common ground/anode connection needed.

## Installation

Download as ZIP → Arduino IDE → Sketch → Include Library → Add .ZIP
Library, or clone into your sketchbook's `libraries` folder:

```
cd ~/Documents/Arduino/libraries
git clone https://github.com/YOUR_USERNAME/Segment188.git
```

## Usage

```cpp
#include <Segment188.h>

Segment188 segment(PA0, PA1, PA2, PA3, PA4); // datasheet pins 1,2,3,4,5

void setup() {
  segment.begin();
}

void loop() {
  segment.update();        // call every loop() pass — non-blocking
  segment.setValue(147);   // call whenever the value changes
}
```

## API

| Function | Description |
|---|---|
| `Segment188(p1, p2, p3, p4, p5)` | Constructor — 5 GPIO pins, mapped to datasheet pins 1–5 in order. |
| `begin()` | Call once in `setup()`. |
| `setValue(uint16_t value)` | 0–199. 100+ lights the leading "1". |
| `update()` | Call every `loop()` pass. Non-blocking. |
| `setStepInterval(unsigned long us)` | Scan speed; default 300µs/segment. |
| `clear()` | Turn the display off. |

The segment-to-pin mapping (derived from the datasheet's pin diagram) is
documented in comments at the top of `src/Segment188.cpp` — edit it there
if your part's wiring differs.

## License

MIT — see [LICENSE](LICENSE).
