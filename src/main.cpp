#include <Arduino.h>
#include "Display.hpp"
#include "Clock.hpp"
#include "Config.hpp"
#include "WifiConfig.hpp"
#include "HttpClient.hpp"
#include "Decoration.hpp"
#include "Ball.hpp"
#include <Ticker.h>

HttpClient httpClient(DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
Display display;
Clock clockRenderer(0, 0);
Ticker clockTicker;
Ball ballRenderer(16, 0, 16, 8, 200);
Decoration decorationRenderer1(16, 0, (int[]){0}, 1, 0);
Decoration decorationRenderer2(24, 0, (int[]){1}, 1, 0);

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
  // display.attachRenderer(&ballRenderer, 1);
  display.attachRenderer(&decorationRenderer1, 1);
  display.attachRenderer(&decorationRenderer2, 2);
  display.init();

  clockTicker.attach(60 * 60, updateClock);
  updateClock();
}

void loop()
{
  httpClient.maintainConnection();
  display.update();
}
