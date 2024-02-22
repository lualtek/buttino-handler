#include "ButtinoHandler.h"

int counterClick = 0;
unsigned long lastClickTime = 0;
unsigned long startLongPressTime = 0;

void wakeupCallback()
{
  BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Woke up");
  delay(200);

  startLongPressTime = millis();
  // Check if reboot is requested while long pressing
  while (digitalRead(BUTTINOHANDLER_PIN) == LOW)
  {
    if (millis() - startLongPressTime > BUTTINOHANDLER_REBOOT_DELAY)
    {
      BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Long pressed, rebooting...");
      api.system.reboot();
    }

    BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Long press time: %d", millis() - startLongPressTime);
  }

  counterClick++;

  // Reset counter click to 1 if the time between clicks is greater than the reset timer
  if (millis() - lastClickTime > BUTTINOHANDLER_CLICK_RESET_TIMER && counterClick > 1)
  {
    BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Resetting counter click");
    lastClickTime = millis();
    counterClick = 1;
    return;
  }

  // If the counter click is greater than the restart value, then we should put the device to sleep
  if (counterClick >= BUTTINOHANDLER_COUNTER_CLICK_SLEEP)
  {
    BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Clicked 5 times, shutting down...");
    counterClick = 0;
    while (1)
    {
      api.system.sleep.setup(RUI_WAKEUP_FALLING_EDGE, BUTTINOHANDLER_PIN);
      api.system.sleep.all(0); // Set to sleep forever.
      pinMode(BUTTINOHANDLER_PIN, INPUT_PULLUP);
      delay(BUTTINOHANDLER_REBOOT_DELAY); // Long press to turn off/on, the long press time is 5s.
      if (digitalRead(BUTTINOHANDLER_PIN) == LOW)
      {
        BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Long pressed, rebooting...");
        api.system.reboot();
      }
    }
  }

  lastClickTime = millis();

  BUTTINOLOG(F("ButtinoHandler .wakeupCallback()"), "Counter click %d", counterClick);
}

ButtinoHandler::ButtinoHandler()
{
}

void ButtinoHandler::begin(int pin = BUTTINOHANDLER_PIN)
{
  _pin = pin;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(_pin, INPUT_PULLUP);
}
