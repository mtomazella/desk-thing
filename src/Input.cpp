#include "Input.hpp"

void InputManager::init()
{
  for (uint8_t i = 0; i < buttonCount; ++i)
  {
    if (buttonPins[i] == CS_PIN)
    {
      continue;
    }

    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonStable[i] = digitalRead(buttonPins[i]) == LOW;
    buttonReading[i] = buttonStable[i];
    buttonChangeAt[i] = millis();
    buttonPressedAt[i] = 0;
    buttonFirstReleaseAt[i] = 0;
    buttonLongSent[i] = false;
    buttonPressPending[i] = false;
  }

  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  encoderLastState =
      (digitalRead(ENCODER_A) << 1) |
      digitalRead(ENCODER_B);
  encoderState = encoderLastState;
  clear();
}

void InputManager::poll()
{
  unsigned long now = millis();

  for (uint8_t i = 0; i < buttonCount; ++i)
  {
    if (buttonPins[i] == CS_PIN)
    {
      continue;
    }

    bool pressed = digitalRead(buttonPins[i]) == LOW;

    if (pressed != buttonReading[i])
    {
      buttonReading[i] = pressed;
      buttonChangeAt[i] = now;
    }

    if (buttonReading[i] != buttonStable[i] &&
        now - buttonChangeAt[i] >= debounceMillis)
    {
      buttonStable[i] = buttonReading[i];
      if (buttonStable[i])
      {
        buttonPressedAt[i] = now;
        buttonLongSent[i] = false;
      }
      else
      {
        unsigned long heldFor = now - buttonPressedAt[i];
        if (heldFor >= longPressMillis)
        {
          buttonPressPending[i] = false;
          if (!buttonLongSent[i])
          {
            enqueue(buttonEvent(i, 2));
          }
        }
        else if (buttonPressPending[i])
        {
          enqueue(buttonEvent(i, 1));
          buttonPressPending[i] = false;
        }
        else
        {
          buttonPressPending[i] = true;
          buttonFirstReleaseAt[i] = now;
        }
      }
    }

    if (buttonStable[i] &&
        !buttonLongSent[i] &&
        now - buttonPressedAt[i] >= longPressMillis)
    {
      buttonLongSent[i] = true;
      buttonPressPending[i] = false;
      enqueue(buttonEvent(i, 2));
    }

    if (!buttonStable[i] &&
        buttonPressPending[i] &&
        now - buttonFirstReleaseAt[i] >= doublePressMillis)
    {
      enqueue(buttonEvent(i, 0));
      buttonPressPending[i] = false;
    }
  }

  uint8_t current =
      (digitalRead(ENCODER_A) << 1) |
      digitalRead(ENCODER_B);

  if (current == encoderState)
  {
    return;
  }

  encoderState = current;
  if ((encoderLastState == 0 && current == 1) ||
      (encoderLastState == 1 && current == 3) ||
      (encoderLastState == 3 && current == 2) ||
      (encoderLastState == 2 && current == 0))
  {
    enqueue(InputEvent::EncoderRight);
  }
  else if ((encoderLastState == 0 && current == 2) ||
           (encoderLastState == 2 && current == 3) ||
           (encoderLastState == 3 && current == 1) ||
           (encoderLastState == 1 && current == 0))
  {
    enqueue(InputEvent::EncoderLeft);
  }

  encoderLastState = current;
}

bool InputManager::available() const
{
  return eventHead != eventTail;
}

InputEvent InputManager::read()
{
  if (!available())
  {
    return InputEvent::None;
  }

  InputEvent event = eventQueue[eventHead];
  eventHead = (eventHead + 1) % eventQueueSize;
  return event;
}

void InputManager::clear()
{
  eventHead = 0;
  eventTail = 0;
}

void InputManager::enqueue(InputEvent event)
{
  uint8_t next = (eventTail + 1) % eventQueueSize;
  if (next == eventHead)
  {
    eventHead = (eventHead + 1) % eventQueueSize;
  }

  eventQueue[eventTail] = event;
  eventTail = next;
}

InputEvent InputManager::buttonEvent(uint8_t index, uint8_t action) const
{
  static const InputEvent pressEvents[5][3] = {
      {InputEvent::EncoderButtonPress, InputEvent::EncoderButtonDoublePress, InputEvent::EncoderButtonLongPress},
      {InputEvent::Button1Press, InputEvent::Button1DoublePress, InputEvent::Button1LongPress},
      {InputEvent::Button2Press, InputEvent::Button2DoublePress, InputEvent::Button2LongPress},
      {InputEvent::Button3Press, InputEvent::Button3DoublePress, InputEvent::Button3LongPress},
      {InputEvent::Button4Press, InputEvent::Button4DoublePress, InputEvent::Button4LongPress}};

  if (index >= buttonCount || action > 2)
  {
    return InputEvent::None;
  }
  return pressEvents[index][action];
}
