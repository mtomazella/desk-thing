#pragma once

#include "Input.hpp"

class Display;
class Clock;

class StateManager
{
public:
  StateManager(InputManager &inputManager, Display &display, Clock &clock);
  void listen();

private:
  InputManager &inputManager;
  Display &display;
  Clock &clock;

  static bool isButtonEvent(InputEvent event);
};
