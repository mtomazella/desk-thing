#include "Clock.hpp"

void Clock::render(Display display) {
  display.mx.setFont(nullptr);
  display.writeAt(0, 0, "12:34");
}