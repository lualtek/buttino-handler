## ButtinoHandler Library

The ButtinoHandler library is an opinionated library for Arduino that allows you to easily put your RAK3172 device into sleep mode by pressing a button. This simplifies power management and conserves battery life in your projects.

### Hardware

This library assumes you have are using a RAK3172 and a momentary button.

### Features

- **Sleep activation**: Put the device into sleep mode by pressing the button a configurable number of times (default: 5).
- **Device reboot/power-on**: Trigger a system reboot or power-on by performing a long press on the button.

### Installation

You can install the ButtinoHandler library through the Arduino Library Manager or manually as a ZIP file.

### Arduino Library Manager (Recommended)

1. Open the Arduino IDE.
2. Go to **Sketch** -> **Include Library** -> **Manage Libraries**.
3. In the Library Manager, search for "ButtinoHandler".
4. Click on the ButtinoHandler library and click the **Install** button.

### Manual Installation

1. Download the ButtinoHandler library as a ZIP file from the GitHub repository: [https://github.com/placeholder](https://github.com/placeholder).
2. In the Arduino IDE, navigate to **Sketch** -> **Include Library** -> **Add .ZIP Library**.
3. Select the downloaded ZIP file of the library and click **Open**.

### Dependencies

The ButtinoHandler library depends on the following libraries:

- [AceButton (>= 1.10)](https://github.com/bxparks/AceButton): A flexible library for handling button presses and long presses.

### Usage

### Wiring

1. Connect a the momentary button to the digital pin `WB_IO4` of the RAK3172.
2. Connect the RAK3172 to the pc using a USB cable.

### Library Initialization

To begin using the ButtinoHandler library, include the library header at the beginning of your sketch:

```c++
#include <ButtinoHandler.h>
```

Next, create an instance of the `ButtonHandler` class:

```c++
ButtinoHandler buttinoHandler;
```

#### Setup

In the `setup()` function, initialize the ButtinoHandler library by calling the `begin()` method:

```c++
void setup() {
  buttinoHandler.begin();
}
```

#### Loop

In the `loop()` function, call the `handle()` method to handle the button presses:

```c++
void loop() {
  buttinoHandler.handle();
}
```

### NOTE on debugging

The ButtinoHandler library uses the `Serial` object to print debug messages and it enabled by default right now. If you want to disable it, you can by defining the `BUTTINOHANDLER_DEBUG` build variable to `0` before building your sketch.

### Contribution

We welcome contributions to the ButtinoHandler library! Please fork the repository on GitHub and submit pull requests for any changes or improvements.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
