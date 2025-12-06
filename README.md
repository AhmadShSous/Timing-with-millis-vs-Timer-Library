# Question 2 — Timing with millis() vs Timer1 (ATmega328P)

A greenhouse fan must:
- Run **ON** for **5 seconds**
- Stay **OFF** for **3 seconds**

This repository contains two implementations:
1. `main_millis.ino` → Using `millis()` (non-blocking)
2. `main_timer1.ino` → Using **Timer1 interrupt** (CTC mode on ATmega328P)

---

## 🔌 Hardware Connections (for both versions)

| Component | MCU Pin       | Notes |
|---|---:|---|
| LED (simulating fan) | PB4 (Arduino D12 on some pinouts) | Anode to PB4, cathode to GND via 220Ω resistor |
| (Optional) Button | any digital pin | to toggle or test manually (not used in example) |

**Wiring**:
- Connect LED anode to digital pin corresponding to PB4 (check your board pin mapping), cathode to GND through 220Ω resistor.
- Power the Arduino / ATmega328P normally.

---

## 🧾 Files

- `main_millis.ino` — millis() implementation (non-blocking)
- `main_timer1.ino` — Timer1 interrupt implementation (CTC, 1s tick)
- `README.md` — this file

---

## ▶ How to use

1. Open Arduino IDE
2. Copy one of the `.ino` files into a new sketch (or save both as separate sketches)
3. Select board: **Arduino Uno**
4. Upload to the board
5. Observe the LED:
   - Default: LED OFF for 3 seconds, then ON for 5 seconds, repeat.

---

## 🔍 Comparison: Timing Stability & CPU Load

**millis() (software timing)**
- **Stability**: Good for many applications; depends on correct use of `unsigned long` and subtraction pattern to avoid overflow bugs. Millis is derived from timer interrupts internally, so it is reasonably stable.
- **CPU Load**: Low — loop does comparisons; no blocking `delay()` so CPU can do other tasks.
- **Pros**: Simple, easy to add other non-blocking tasks in `loop()`.
- **Cons**: If `loop()` contains long blocking operations (`delay`, heavy computations`), the effective timing can be affected.

**Timer1 Interrupt (hardware)**
- **Stability**: Excellent — timing driven by hardware Timer1. Most stable for periodic tasks.
- **CPU Load**: Very low — ISR executes briefly each tick and main loop is free. Better for precise timing and low-latency tasks.
- **Pros**: Precise, minimal jitter, independent from main loop workload.
- **Cons**: Slightly more complex to implement; must be careful with what is executed inside ISR (keep it short).

**Bottom line**:
- For simple tasks where ± a few ms to tens of ms is acceptable, `millis()` is simpler and fine.
- For stricter timing guarantees or to keep the CPU free for other heavy tasks, use Timer interrupts.

---

##  Testing & TinkerCad

You can simulate both versions on TinkerCad. Replace the link below with your TinkerCad project:

**TinkerCad Project Link:**  
https://www.tinkercad.com/things/6FQdCmcJwY2-brave-tumelo?sharecode=RB3ZpWb78SKlYnT_QvaL2y4OAcdvwcS3a1ODR8LEk9M
**Testing steps**
1. Open the chosen `.ino` sketch in Arduino IDE (or copy to TinkerCad code editor).
2. Upload / Start simulation.
3. Observe the LED timing: OFF for 3s → ON for 5s → repeat.
4. For comparison:
   - In `main_millis.ino`, add a long blocking task in `loop()` (e.g., `delay(2000)`) and observe timing drift.
   - In `main_timer1.ino`, do the same — Timer-driven toggling should remain stable.

---

## ✅ Notes & Improvements
- If you need sub-second resolution in Timer1 solution, set OCR1A to a smaller value (e.g., 1ms tick) and count milliseconds instead of seconds.
- Keep ISR code short: set flags or change simple ports; avoid long processing or heavy library calls inside ISR.
- If you want to measure real jitter, use an oscilloscope to capture the LED signal and compute variance.

---
