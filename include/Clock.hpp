#include "Renderer.hpp"

class Clock : public Renderer {
public:
  Clock(int xOffset, int yOffset) : Renderer(xOffset, yOffset) {}
  void render(Display display) override;
};