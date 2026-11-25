#include <Arduino.h>
#include <Ticker.h>
#include "Display.hpp"
#include "Clock.hpp"
#include "Config.hpp"
#include "WifiConfig.hpp"
#include "HttpClient.hpp"
#include "Decoration.hpp"
#include "Ball.hpp"
#include "Input.hpp"
#include "StateManager.hpp"

HttpClient httpClient(DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
Display display;
Clock clockRenderer(8, 0);
Ticker clockTicker;
Ticker displayTicker;
Ticker restartTicker;
Ball ballRenderer(16, 0, 16, 8, 200);
Decoration decorationRenderer1(0, 0, (int[]){0}, 1, 0);
Decoration decorationRenderer2(24, 0, (int[]){1}, 1, 0);
InputManager inputManager;
StateManager stateManager(inputManager, display, clockRenderer);

void updateClock()
{
  int currentTime = httpClient.getTime();
  if (currentTime != -1)
  {
    clockRenderer.setTime(currentTime);
  }
}

void manageDisplay()
{
  int time = clockRenderer.getTimeString().toInt();
  PRINTS("Current time: ");
  PRINTD(time);

  display.setIntensity(
      (time >= TIME_HIGH_INTENSITY_START && time < TIME_HIGH_INTENSITY_END)
          ? DISPLAY_HIGH_INTENSITY
          : DISPLAY_LOW_INTENSITY);
  display.setEnabled((time >= TIME_DISPLAY_ENABLED_START && time < TIME_DISPLAY_ENABLED_END));
}

void setup()
{
#if DEBUG
  Serial.begin(115200);
#endif

  httpClient.init();

  display.attachRenderer(&clockRenderer, 0);
  // display.attachRenderer(&ballRenderer, 1);
  display.attachRenderer(&decorationRenderer1, 1);
  display.attachRenderer(&decorationRenderer2, 2);
  display.init();
  inputManager.init();

  clockTicker.attach(60 * 15, updateClock);
  displayTicker.attach(15, manageDisplay);
  restartTicker.attach(60 * 15, []()
                       { ESP.restart(); });
  updateClock();
  manageDisplay();
}

void loop()
{
  httpClient.maintainConnection();
  stateManager.listen();

  if (clockRenderer.isAlarmActive() || millis() - stateManager.getLastEventTime() < TIME_DISPLAY_ENABLE_ON_INPUT)
  {
    display.setEnabled(true);
  }

  display.update();
}
