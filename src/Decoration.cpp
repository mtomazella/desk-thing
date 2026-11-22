#include <Arduino.h>
#include "Decoration.hpp"
#include "Font.hpp"

void Decoration::render(Display &display)
{
  long now = millis();
  if (now - lastUpdate > 60000)
  {
    lastUpdate = now;
    if (random(0, 100) < chance * 100)
    {
      selectedCharacter = random(0, characterCount);
    }
  }

  Serial.println(characterList[selectedCharacter]);

  display.mx.setFont(decorationFont);
  display.writeCharacter(xOffset, yOffset, (char)characterList[selectedCharacter]);
}