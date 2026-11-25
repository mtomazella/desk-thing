#pragma once
#include <SPI.h>
#include <MD_MAX72xx.h>
#include "Config.hpp"

class Renderer;

class Display
{
public:
  MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
  Display();

  void init();
  void update();
  int getCharWidth(char character);
  bool needsSpace(char character);
  void writeCharacter(int x, int y, char character);
  void writeAt(int x, int y, String text);
  void attachRenderer(Renderer *renderer, int index);
  void setIntensity(int intensity) { this->intensity = intensity; }
  void setEnabled(bool enabled) { this->enabled = enabled; }

private:
  Renderer *renderer[MAX_RENDERERS];
  int intensity = 0;
  bool enabled = true;
};