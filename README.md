# Segment188

Arduino library for driving the 188-type charlieplexed LED digital segment display. Displays values 0–199 using 5 GPIO pins and no extra driver hardware.


![Wiring diagram](images/wiring.png)

Hardware Setup
--------------
Uses 5 digital pins, charlieplexed — no common ground/anode wiring needed. Each pin needs its own series resistor (start at 100Ω, tune for brightness — 1 resistor per pin, not per LED, since charlieplexing routes segment current through pin pairs). Avoid pins with a fixed hardware pull-up/pull-down or reserved boot/debug function on your board.

Wire the 5 pins in datasheet order (1–5) and pass them to the constructor in that order, e.g. `Segment188(PA0, PA1, PA2, PA3, PA4)`.

Repository Contents
-------------------
* **/examples** - Arduino example sketches


Usage
-----
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

Documentation

License Information
-------------------
MIT — see [LICENSE](LICENSE).
