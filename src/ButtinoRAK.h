#ifndef _ButtinoRAK_H_
#define _ButtinoRAK_H_

#include <Arduino.h>

#define BUTTINORAK_PIN WB_IO4
#define BUTTINORAK_CLICK_RESET_TIMER 2500
#define BUTTINORAK_REBOOT_DELAY 3000
#define BUTTINORAK_COUNTER_CLICK_SLEEP 5

// Debug output set to 0 to disable app debug output
#ifndef BUTTINORAK_DEBUG
#define BUTTINORAK_DEBUG 1
#endif

#if BUTTINORAK_DEBUG > 0
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

class ButtinoRAK
{
public:
  /**
   * @brief Construct a new ButtinoRAK object
   */
  ButtinoRAK();

  /**
   * @brief Begin the ButtinoRAK
   * It should be called in the setup() function of the Arduino sketch.
   * @param pin The pin number of the button (default: BUTTINORAK_PIN = WB_IO4)
   */
  void begin(int pin);
  void begin();

private:
  int _pin = BUTTINORAK_PIN;
};

#endif
