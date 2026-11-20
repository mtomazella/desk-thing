#include <Arduino.h>
#include "Display.hpp"

Display display;

void setup()
{
  Serial.begin(115200);
  display.init();
}

void loop()
{
  display.update();
}
