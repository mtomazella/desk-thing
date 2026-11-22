#include "Clock.hpp"
#include "Display.hpp"
#include "Font.hpp"

void Clock::render(Display &display)
{
  display.mx.setFont(clockFont);
  display.writeAt(0, 0, getTimeString());
}

String Clock::getTimeString()
{
  long now = millis();
  long delta = now - lastUpdate;

  if (delta >= 1000)
  {
    unixtime += delta / 1000;
    lastUpdate = now;
  }

  int hours = ((unixtime % 86400L) / 3600) + TIMEZONE_OFFSET;
  if (hours < 0)
  {
    hours += 24;
  }
  else if (hours >= 24)
  {
    hours -= 24;
  }
  int minutes = (unixtime % 3600) / 60;
  char buffer[5];
  snprintf(buffer, sizeof(buffer), "%02d%02d", hours, minutes);

  return String(buffer);
}
