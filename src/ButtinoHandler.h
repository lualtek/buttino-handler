#ifndef _ButtinoHandler_H_
#define _ButtinoHandler_H_

#include <Arduino.h>
#include <AceButton.h>

#define BUTTINOHANDLER_PIN WB_IO4
#define BUTTINOHANDLER_CLICK_RESET_TIMER 1000
#define BUTTINOHANDLER_REBOOT_DELAY 3000
#define BUTTINOHANDLER_COUNTER_CLICK_RESTART 5

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
   */
  void begin();

  /**
   * @brief Handle the button event
   * It should be called in the loop() function of the Arduino sketch.
   */
  void handle();

private:
};

#endif
