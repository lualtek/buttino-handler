#ifndef _ButtinoHandler_H_
#define _ButtinoHandler_H_

#include <Arduino.h>

#define BUTTINOHANDLER_PIN WB_IO4
#define BUTTINOHANDLER_CLICK_RESET_TIMER 2500
#define BUTTINOHANDLER_REBOOT_DELAY 3000
#define BUTTINOHANDLER_COUNTER_CLICK_SLEEP 5

// Debug output set to 0 to disable app debug output
#ifndef BUTTINOHANDLER_DEBUG
#define BUTTINOHANDLER_DEBUG 1
#endif

#if BUTTINOHANDLER_DEBUG > 0
#define BUTTINOLOG(tag, ...)       \
  do                               \
  {                                \
    if (tag)                       \
      Serial.printf("[%s] ", tag); \
    Serial.printf(__VA_ARGS__);    \
    Serial.printf("\n");           \
  } while (0)
#else
#define BUTTINOLOG(...)
#endif

void wakeupCallback();

class ButtinoHandler
{
public:
  /**
   * @brief Construct a new ButtinoHandler object
   */
  ButtinoHandler();

  /**
   * @brief Begin the ButtinoHandler
   * It should be called in the setup() function of the Arduino sketch.
   * @param pin The pin number of the button (default: BUTTINOHANDLER_PIN = WB_IO4)
   */
  void begin(int pin = BUTTINOHANDLER_PIN);

private:
  int _pin = BUTTINOHANDLER_PIN;
};

#endif
