#include "ButtinoRAK.h"

int counterClick = 0;
unsigned long lastClickTime = 0;
unsigned long startLongPressTime = 0;

void wakeupCallback()
{
  BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Woke up");
  delay(200);

  startLongPressTime = millis();
  // Check if reboot is requested while long pressing
  while (digitalRead(BUTTINORAK_PIN) == LOW)
  {
    if (millis() - startLongPressTime > BUTTINORAK_REBOOT_DELAY)
    {
      BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Long pressed, rebooting...");
      api.system.reboot();
    }

    BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Long press time: %d", millis() - startLongPressTime);
  }

  counterClick++;

  // Reset counter click to 1 if the time between clicks is greater than the reset timer
  if (millis() - lastClickTime > BUTTINORAK_CLICK_RESET_TIMER && counterClick > 1)
  {
    BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Resetting counter click");
    lastClickTime = millis();
    counterClick = 1;
    return;
  }

  // If the counter click is greater than the restart value, then we should put the device to sleep
  if (counterClick >= BUTTINORAK_COUNTER_CLICK_SLEEP)
  {
    BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Clicked 5 times, shutting down...");
    counterClick = 0;
    while (1)
    {
      api.system.sleep.setup(RUI_WAKEUP_FALLING_EDGE, BUTTINORAK_PIN);
      api.system.sleep.all(0); // Set to sleep forever.
      pinMode(BUTTINORAK_PIN, INPUT_PULLUP);
      delay(BUTTINORAK_REBOOT_DELAY); // Long press to turn off/on, the long press time is 5s.
      if (digitalRead(BUTTINORAK_PIN) == LOW)
      {
        BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Long pressed, rebooting...");
        api.system.reboot();
      }
    }
  }

  lastClickTime = millis();

  BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Counter click %d", counterClick);
}

ButtinoRAK::ButtinoRAK()
{
}

void ButtinoRAK::begin(int pin = BUTTINORAK_PIN)
{
  _pin = pin;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(_pin, INPUT_PULLUP);
}

void ButtinoRAK::begin()
{
  _pin = BUTTINORAK_PIN;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(_pin, INPUT_PULLUP);
}
