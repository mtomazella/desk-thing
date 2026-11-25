#pragma once

#include "Input.hpp"

class Display;
class Clock;

class StateManager
{
public:
  StateManager(InputManager &inputManager, Display &display, Clock &clock);
  void listen();
  long getLastEventTime() const { return lastEventTime; }

private:
  InputManager &inputManager;
  Display &display;
  Clock &clock;
  long lastEventTime = 0;

  static bool isButtonEvent(InputEvent event);
};
