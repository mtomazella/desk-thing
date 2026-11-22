#include <Arduino.h>
#include "Display.hpp"
#include "Clock.hpp"
#include "Config.hpp"
#include "WifiConfig.hpp"
#include "HttpClient.hpp"
#include <Ticker.h>

HttpClient httpClient(DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
Display display;
Clock clockRenderer(0, 0);
Ticker clockTicker;

void updateClock()
{
  int currentTime = httpClient.getTime();
  if (currentTime != -1)
  {
    clockRenderer.setTime(currentTime);
  }
}

void setup()
{
  Serial.begin(115200);

  httpClient.init();

  display.attachRenderer(&clockRenderer, 0);
  display.init();

  clockTicker.attach(60 * 60, updateClock);
  updateClock();
}

void loop()
{
  httpClient.maintainConnection();
  display.update();
}
