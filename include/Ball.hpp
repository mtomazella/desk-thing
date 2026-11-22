#include <Arduino.h>
#include "Renderer.hpp"
#include "Display.hpp"

class Ball : public Renderer
{
public:
  Ball(int xOffset, int yOffset, int width, int height, int refreshRate) : Renderer(xOffset, yOffset, width, height), refreshRate(refreshRate)
  {
    x = random(0, width);
    y = random(0, height);
  }
  void render(Display &display) override;

private:
  int lastUpdate = 0;
  int refreshRate = 100;
  int x = 2;
  int y = 0;
  int xVel = 1;
  int yVel = 1;
};