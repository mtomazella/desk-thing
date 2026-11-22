#pragma once
#include <Arduino.h>
#include "Renderer.hpp"

class Clock : public Renderer
{
public:
  Clock(int xOffset, int yOffset) : Renderer(xOffset, yOffset) {}
  void render(Display &display) override;
  String getTimeString();
  void setTime(long newTime) { unixtime = newTime; }

private:
  long unixtime = 0;
  long lastUpdate = 0;
};