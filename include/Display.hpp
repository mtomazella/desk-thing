#pragma once
#include <SPI.h>
#include <MD_MAX72xx.h>
#include "Config.hpp"

typedef unsigned int Frame[FRAME_HEIGHT];

class Display
{
private:
  MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
  Frame frame1;
  Frame frame2;
  Frame *currentFrame;
  Frame *nextFrame;
  void swapFrames();
  void clearFrame(Frame *frame);
  bool compareFrames(Frame *frameA, Frame *frameB);
  void drawFrame(Frame *frame);
  int getCharWidth(char character);
  bool needsSpace(char character);

public:
  Display();
  void init();
  void update();
  void writeCharacter(int x, int y, char character);
  void writeAt(int x, int y, String text);
};