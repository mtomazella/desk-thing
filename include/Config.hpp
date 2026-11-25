#define DEVICE_NAME "Desk Thing"

// HARDWARE
#define CLK_PIN 14  // or SCK
#define DATA_PIN 13 // or MOSI
#define CS_PIN 12   // or SS
#define ENCODER_A 4
#define ENCODER_B 2
#define ENCODER_BTN 15
#define BTN_1 23
#define BTN_2 21
#define BTN_3 19
#define BTN_4 18
#define BUZZER 16

// CLOCK
#define TIMEZONE_OFFSET -3
#define ALARM_DURATION 5 // in minutes
#define ALARM_BEEP_DURATION 500 // in milliseconds
#define ALARM_BEEP_SILENCE_DURATION 500 // in milliseconds
#define ALARM_BEEP_FREQUENCY 2700 // in Hertz; 2700Hz is resonant frequency for my buzzer
#define MAX_ALARMS 10
#define ALARMS {630, 1144, -1, -1, -1, -1, -1, -1, -1, -1}

// DISPLAY
#define USE_LOCAL_FONT 1
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DELAYTIME 100 // in milliseconds
#define COL_1 MAX_DEVICES * 8 - 1
#define SPACE_SIZE 1
#define MAX_RENDERERS 4
#define display_x(x) (COL_1 - x)

// DEBUG
#define DEBUG 0

#if DEBUG
#define PRINT(s, x)     \
  {                     \
    Serial.print(F(s)); \
    Serial.print(x);    \
  }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)
#define PRINTLN(s)

#endif