#pragma once

#include <Arduino.h>
#include "Config.hpp"

enum class InputEvent
{
  None,
  EncoderLeft,
  EncoderRight,
  EncoderButtonPress,
  EncoderButtonDoublePress,
  EncoderButtonLongPress,
  Button1Press,
  Button1DoublePress,
  Button1LongPress,
  Button2Press,
  Button2DoublePress,
  Button2LongPress,
  Button3Press,
  Button3DoublePress,
  Button3LongPress,
  Button4Press,
  Button4DoublePress,
  Button4LongPress
};

class InputManager
{
public:
  void init();
  void poll();
  bool available() const;
  InputEvent read();
  void clear();

private:
  static const uint8_t buttonCount = 5;
  static const uint8_t eventQueueSize = 16;
  static const unsigned long debounceMillis = 20;
  static const unsigned long doublePressMillis = 300;
  static const unsigned long longPressMillis = 800;

  const uint8_t buttonPins[buttonCount] = {
      ENCODER_BTN,
      BTN_1,
      BTN_2,
      BTN_3,
      BTN_4};
  bool buttonStable[buttonCount] = {false, false, false, false, false};
  bool buttonReading[buttonCount] = {false, false, false, false, false};
  unsigned long buttonChangeAt[buttonCount] = {0, 0, 0, 0, 0};
  unsigned long buttonPressedAt[buttonCount] = {0, 0, 0, 0, 0};
  unsigned long buttonFirstReleaseAt[buttonCount] = {0, 0, 0, 0, 0};
  bool buttonLongSent[buttonCount] = {false, false, false, false, false};
  bool buttonPressPending[buttonCount] = {false, false, false, false, false};

  uint8_t encoderState = 0;
  uint8_t encoderLastState = 0;
  InputEvent eventQueue[eventQueueSize];
  uint8_t eventHead = 0;
  uint8_t eventTail = 0;

  void enqueue(InputEvent event);
  InputEvent buttonEvent(uint8_t index, uint8_t action) const;
};