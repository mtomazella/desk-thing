#pragma once
#include <Arduino.h>
#include "Config.hpp"
#include "Renderer.hpp"

class Clock : public Renderer
{
public:
  Clock(int xOffset, int yOffset) : Renderer(xOffset, yOffset) {}
  void render(Display &display) override;
  String getTimeString();
  void setTime(long newTime) { unixtime = newTime; }
  void addAlarm(int alarmTime);
  void stopAlarm();
  bool handleAlarms(Display &display);

private:
  long unixtime = 0;
  long lastUpdate = 0;
  int alarms[MAX_ALARMS] = ALARMS;
  int lastAlarmStop = -1;
  long lastBeep = 0;
};