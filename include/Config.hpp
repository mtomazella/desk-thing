#define USE_LOCAL_FONT 1
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 14    // or SCK
#define DATA_PIN 13   // or MOSI
#define CS_PIN 12     // or SS
#define DELAYTIME 100 // in milliseconds

#define COL_1 MAX_DEVICES * 8 - 1
#define SPACE_SIZE 1
#define MAX_RENDERERS 4

#define display_x(x) (COL_1 - x)

#define DEBUG 1

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

#endif

#define DEVICE_NAME "Desk Thing"
#define TIMEZONE_OFFSET -3