#include "ButtinoRAK.h"

int counterClick = 0;
bool isSleeping = false;
unsigned long lastClickTime = 0;
unsigned long startLongPressTime = 0;
int __pin;

void wakeupCallback()
{
  BUTTINOLOG(F("ButtinoRAK .wakeupCallback()"), "Woke up");
  delay(200);

  startLongPressTime = millis();
  // Check if reboot is requested while long pressing
  while (digitalRead(__pin) == LOW)
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
    api.system.timer.stop(RAK_TIMER_0);
    api.lorawan.deviceClass.set(RAK_LORA_CLASS_A);
    isSleeping = true;
    api.system.sleep.setup(RUI_WAKEUP_FALLING_EDGE, __pin);
    api.system.sleep.all(0); // Set to sleep forever.
    return;
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
  __pin = _pin;
  _begin();
}

void ButtinoRAK::begin()
{
  _pin = BUTTINORAK_PIN;
  __pin = _pin;
  _begin();
}

void ButtinoRAK::_begin()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(_pin, INPUT_PULLUP);
  attachInterrupt(_pin, wakeupCallback, FALLING);
}
