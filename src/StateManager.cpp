#include "StateManager.hpp"
#include "Clock.hpp"
#include "Display.hpp"

StateManager::StateManager(
    InputManager &inputManager,
    Display &display,
    Clock &clock) : inputManager(inputManager),
                    display(display),
                    clock(clock),
                    lastEventTime(millis() + TIME_DISPLAY_ENABLE_ON_INPUT + 1) {}

void StateManager::listen()
{
  inputManager.poll();

  if (!inputManager.available())
    return;

  InputEvent event = inputManager.read();
  PRINTS("Event: ");
  PRINTD(static_cast<int>(event));

  lastEventTime = millis();

  if (isButtonEvent(event) && clock.isAlarmActive())
  {
    clock.stopAlarm();
    display.mx.clear();
  }
}

bool StateManager::isButtonEvent(InputEvent event)
{
  switch (event)
  {
  case InputEvent::EncoderButtonPress:
  case InputEvent::EncoderButtonDoublePress:
  case InputEvent::EncoderButtonLongPress:
  case InputEvent::Button1Press:
  case InputEvent::Button1DoublePress:
  case InputEvent::Button1LongPress:
  case InputEvent::Button2Press:
  case InputEvent::Button2DoublePress:
  case InputEvent::Button2LongPress:
  case InputEvent::Button3Press:
  case InputEvent::Button3DoublePress:
  case InputEvent::Button3LongPress:
  case InputEvent::Button4Press:
  case InputEvent::Button4DoublePress:
  case InputEvent::Button4LongPress:
    return true;
  default:
    return false;
  }
}
