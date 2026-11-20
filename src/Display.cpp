#include <Arduino.h>
#include "Display.hpp"
#include "Font.hpp"

Display::Display()
{
  currentFrame = &frame1;
  nextFrame = &frame2;
  clearFrame(currentFrame);
  clearFrame(nextFrame);
}

void Display::init()
{
  if (!mx.begin())
  {
    Serial.println("Failed to initialize MD_MAX72XX");
  }
  mx.clear();
  mx.setFont(bit3font);
  writeAt(0, 0, "Hello");
  return;
}

void Display::update()
{
  mx.update();
}

void Display::swapFrames()
{
  if (currentFrame == &frame1)
  {
    currentFrame = &frame2;
  }
  else
  {
    currentFrame = &frame1;
  }
  clearFrame(currentFrame);
}

void Display::clearFrame(Frame *frame)
{
  for (int i = 0; i < FRAME_HEIGHT; ++i)
  {
    (*frame)[i] = 0;
  }
}

bool Display::compareFrames(Frame *frameA, Frame *frameB)
{
  for (int i = 0; i < FRAME_HEIGHT; ++i)
  {
    if ((*frameA)[i] != (*frameB)[i])
    {
      return false;
    }
  }
  return true;
}

void Display::drawFrame(Frame *frame)
{
  for (int y = 0; y < FRAME_HEIGHT; ++y)
  {
    for (int x = 0; x < FRAME_WIDTH; ++x)
    {
      bool pixelValue = ((*frame)[y] >> x) & 1;
      Serial.print(pixelValue ? "■" : "□");
    }
    Serial.println();
  }
}

void Display::writeCharacter(int x, int y, char character)
{
  mx.setChar(COL_1 - x, character);
}

int Display::getCharWidth(char character)
{
  MD_MAX72XX::fontType_t *fontData = mx.getFont();
  MD_MAX72XX::fontInfo_t fontInfo = mx.getFontInfo();

  int32_t offset = fontInfo.dataOffset;
  uint16_t characterNumber = (uint16_t)character;

  if (characterNumber < fontInfo.firstASCII || characterNumber > fontInfo.lastASCII)
    offset = -1;
  else
  {
    for (uint16_t i = fontInfo.firstASCII; i < characterNumber; i++)
    {
      offset += pgm_read_byte(fontData + offset);
      offset++; // skip size byte we used above
    }
  }

  return (fontData[offset]);
}

bool Display::needsSpace(char character)
{
  int charNumber = (int)character;
  if (charNumber >= 65 && charNumber <= 90) // A-Z
    return true;
  if (charNumber >= 97 && charNumber <= 122) // a-z
    return true;
  if (charNumber >= 48 && charNumber <= 57) // 0-9
    return true;
  return false;
}

void Display::writeAt(int x, int y, String text)
{
  for (int i = 0; i < text.length(); ++i)
  {
    char character = text.charAt(i);
    writeCharacter(x, y, character);
    x += getCharWidth(character);
    if ((i + 1) < text.length())
      x += (int)needsSpace(text.charAt(i + 1)) * SPACE_SIZE;
  }
}