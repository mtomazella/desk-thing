#pragma once

class Display;

class Renderer
{
public:
  Renderer(
      int xOffset,
      int yOffset) : xOffset(xOffset),
                     yOffset(yOffset),
                     width(8),
                     height(8) {}
  Renderer(
      int xOffset,
      int yOffset,
      int width,
      int height) : xOffset(xOffset),
                    yOffset(yOffset),
                    width(width),
                    height(height) {}
  virtual void render(Display &display);

protected:
  int xOffset = 0;
  int yOffset = 0;
  int width = 0;
  int height = 0;
};