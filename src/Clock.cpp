#include "Clock.hpp"
#include "Display.hpp"
#include "Font.hpp"

void Clock::render(Display &display)
{
  if (handleAlarms(display))
  {
    return;
  }
  display.mx.setFont(clockFont);
  display.writeAt(xOffset, 0, getTimeString());
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

void Clock::addAlarm(int alarmTime)
{
  for (int i = 0; i < MAX_ALARMS; i++)
  {
    if (alarms[i] == -1)
    {
      alarms[i] = alarmTime;
      break;
    }
  }
}

void Clock::stopAlarm()
{
  lastAlarmStop = unixtime;
  noTone(BUZZER);
}

bool Clock::isAlarmActive()
{
  int time = getTimeString().toInt();

  for (int i = 0; i < MAX_ALARMS; i++)
  {
    if (alarms[i] != -1 && alarms[i] <= time) // has alarm and is now or already started
    {
      if (lastAlarmStop < alarms[i])
      { // and has not been stopped
        if (time - alarms[i] < 5)
        { // and has not been beeping for more than 5 minutes
          return true;
          break;
        }
      }
    }
  }
  return false;
}

bool Clock::handleAlarms(Display &display)
{

  if (!isAlarmActive())
  {
    return false;
  }

  long now = millis();
  long delta = now - lastBeep;

  if (delta < ALARM_BEEP_DURATION)
  { // 0-500ms - beep
    for (int y = 0; y < MAX_DEVICES * 8; y++)
    {
      for (int x = 0; x < 8; x++)
      {
        display.mx.setPoint(x, y, true);
      }
    }
    tone(BUZZER, ALARM_BEEP_FREQUENCY);
  }
  else if (delta < (ALARM_BEEP_SILENCE_DURATION + ALARM_BEEP_DURATION))
  { // 500-1000ms - silence
    display.mx.clear();
    noTone(BUZZER);
  }
  else
  { // restart
    lastBeep = now;
  }

  return true;
}