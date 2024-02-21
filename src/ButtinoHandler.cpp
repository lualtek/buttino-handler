#include "ButtinoHandler.h"

using namespace ace_button;

int counterClick = 0;
unsigned long lastClickTime = 0;
bool justWokeUp = false;
unsigned long lastWakeupTime = 0;

void wakeupCallback()
{
  justWokeUp = true;
  lastWakeupTime = millis();
  BUTTINOLOG("ButtinoHandler .wakeupCallback()", "Woke up");
}

void handleEvent(ace_button::AceButton *button, uint8_t eventType, uint8_t buttonState)
{
  switch (eventType)
  {
  case AceButton::kEventLongPressed:
    BUTTINOLOG("ButtinoHandler .handleEvent()", "Long pressed, rebooting...");
    api.system.reboot();
    break;
  case AceButton::kEventClicked:
    counterClick++;
    lastClickTime = millis();
    if (counterClick >= BUTTINOHANDLER_COUNTER_CLICK_RESTART)
    {
      BUTTINOLOG("ButtinoHandler .handleEvent()", "Clicked 5 times, shutting down...");
      api.system.sleep.all();
    }
    break;
  default:
    break;
  }
}

AceButton button;

ButtinoHandler::ButtinoHandler()
{
}

void ButtinoHandler::begin(int pin = BUTTINOHANDLER_PIN)
{
  _pin = pin;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(_pin, INPUT_PULLUP);

  button.setEventHandler(handleEvent);

  ButtonConfig *buttonConfig = button.getButtonConfig();
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setLongPressDelay(BUTTINOHANDLER_REBOOT_DELAY);

  api.system.sleep.setup(RUI_WAKEUP_FALLING_EDGE, _pin);
  if (api.system.sleep.registerWakeupCallback(wakeupCallback) == false)
  {
    BUTTINOLOG("ButtinoHandler .begin()", "Create Wakeup Callback failed.");
  }
}

void ButtinoHandler::handle()
{
  button.check();

  if (millis() - lastClickTime > BUTTINOHANDLER_CLICK_RESET_TIMER)
  {
    counterClick = 0;
  }

  // if justWokeUp flag is true even after the BUTTINOHANDLER_REBOOT_DELAY, then it means the button didn't trigger the long press event, we shoul go back to Sleep
  if (justWokeUp && millis() - lastWakeupTime > BUTTINOHANDLER_REBOOT_DELAY + 2000)
  {
    justWokeUp = false;
    lastWakeupTime = 0;
    BUTTINOLOG("ButtinoHandler .handle()", "Going back to sleep");
    api.system.sleep.all();
  }
}
