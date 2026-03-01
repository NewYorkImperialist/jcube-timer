#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 19
#define DIO 18

TM1637Display display(CLK, DIO);
hw_timer_t *timer;
uint8_t value = 0;

void setup() {
  Serial.begin(115200);
  display.setBrightness(7);

  // divide 80mhz to 1khz
  timer = timerBegin(0, 8000, true);
}

void loop() {
  uint64_t ms = timerReadMilis(timer);
  Serial.println(ms);
  if (ms < 60000) {
    display.showNumberDecEx(ms / 10, 0b01000000, true);
  } else {
    uint64_t ss = timerReadSeconds(timer);
    uint64_t m = ss / 60;
    uint64_t s = ss % 60;
    display.showNumberDecEx(m * 100 + s, 0b01000000, true);
  }
  delay(10);
}
