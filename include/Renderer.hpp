#pragma once

class Display;

class Renderer
{
public:
  Renderer(int xOffset, int yOffset) : xOffset(xOffset), yOffset(yOffset) {}
  virtual void render(Display &display);

private:
  int xOffset = 0;
  int yOffset = 0;
};