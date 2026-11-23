#include <Arduino.h>
#include <Ticker.h>
#include "Display.hpp"
#include "Clock.hpp"
#include "Config.hpp"
#include "WifiConfig.hpp"
#include "HttpClient.hpp"
#include "Decoration.hpp"
#include "Ball.hpp"

HttpClient httpClient(DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
Display display;
Clock clockRenderer(8, 0);
Ticker clockTicker;
Ticker intensityTicker;
Ball ballRenderer(16, 0, 16, 8, 200);
Decoration decorationRenderer1(0, 0, (int[]){0}, 1, 0);
Decoration decorationRenderer2(24, 0, (int[]){1}, 1, 0);

void updateClock()
{
  int currentTime = httpClient.getTime();
  if (currentTime != -1)
  {
    clockRenderer.setTime(currentTime);
  }
}

void manageIntensity()
{
  int time = clockRenderer.getTimeString().toInt();
  if (time >= 600 && time < 2000)
  {
    display.mx.control(MD_MAX72XX::INTENSITY, 15);
  }
  display.mx.control(MD_MAX72XX::INTENSITY, 0);
}

void setup()
{
  Serial.begin(115200);

  httpClient.init();

  display.attachRenderer(&clockRenderer, 0);
  // display.attachRenderer(&ballRenderer, 1);
  display.attachRenderer(&decorationRenderer1, 1);
  display.attachRenderer(&decorationRenderer2, 2);
  display.init();

  clockTicker.attach(60 * 60, updateClock);
  intensityTicker.attach(60, manageIntensity);
  updateClock();
  // clockRenderer.addAlarm(2202);
}

void loop()
{
  httpClient.maintainConnection();
  display.update();
}
