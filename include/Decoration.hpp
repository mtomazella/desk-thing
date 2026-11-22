#include "Renderer.hpp"
#include "Display.hpp"

class Decoration : public Renderer
{
public:
  Decoration(
      int xOffset,
      int yOffset,
      int *characterList,
      int characterCount,
      float chance) : Renderer(xOffset, yOffset),
                      characterList(characterList),
                      characterCount(characterCount),
                      chance(chance) {}
  void render(Display &display) override;

private:
  int *characterList;
  int characterCount;
  int selectedCharacter = 0;
  float chance;
  long lastUpdate = 0;
};