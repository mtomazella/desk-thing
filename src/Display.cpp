#include <Arduino.h>
#include "Display.hpp"
#include "Renderer.hpp"
#include "Font.hpp"

Display::Display()
{
  for (int i = 0; i < MAX_RENDERERS; ++i)
  {
    renderer[i] = nullptr;
  }
}

void Display::init()
{
  if (!mx.begin())
  {
    Serial.println("Failed to initialize MD_MAX72XX");
  }
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();
  return;
}

void Display::update()
{
  for (int i = MAX_RENDERERS - 1; i >= 0; --i)
  {
    if (renderer[i] != nullptr)
    {
      renderer[i]->render(*this);
    }
  }
  mx.update();
}

void Display::attachRenderer(Renderer *renderer, int index)
{
  if (index < 0 || index >= MAX_RENDERERS)
    return;
  this->renderer[index] = renderer;
}

void Display::writeCharacter(int x, int y, char character)
{
  mx.setChar(display_x(x), character);
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