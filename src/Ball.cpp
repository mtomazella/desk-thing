#include "Ball.hpp"

void Ball::render(Display &display)
{
  long now = millis();
  if (now - lastUpdate < refreshRate)
    return;
  lastUpdate = now;

  const int minX = xOffset;
  const int maxX = xOffset + width - 1;
  const int minY = yOffset;
  const int maxY = yOffset + height - 1;

  display.mx.setPoint(y + yOffset, display_x((x + xOffset)), false);
  x += xVel;
  y += yVel;
  display.mx.setPoint(y + yOffset, display_x((x + xOffset)), true);

  if ((y + yOffset == minY) || (y + yOffset == maxY))
    yVel = -yVel;
  if ((x + xOffset == minX) || (x + xOffset == maxX))
    xVel = -xVel;
}