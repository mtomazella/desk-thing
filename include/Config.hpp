#define FRAME_WIDTH 32
#define FRAME_HEIGHT 8

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

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define USE_LOCAL_FONT 1
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define COL_1 MAX_DEVICES * 8 - 1
#define SPACE_SIZE 1

#define CLK_PIN 14    // or SCK
#define DATA_PIN 13   // or MOSI
#define CS_PIN 12     // or SS
#define DELAYTIME 100 // in milliseconds