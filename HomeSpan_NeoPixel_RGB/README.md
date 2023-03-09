# HomeSpan NeoPixel RGB

Using [HomeSpan](https://github.com/HomeSpan/HomeSpan) let´s you create your own HomeKit accessories to your Apple smart home. An ESP32 can be used as a bridge, controlling multiple smart accessories. This example uses just a single addressable RGB LED list, using Adafruit´s NeoPixel library. Other libraries can be used, as seen in examples from HomeSpan. Here is a [tutorial video of installation and set up](https://www.youtube.com/watch?v=FUrjwFKhAwA).


## Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board
- LED´s
 
## Install necessary libraries
Install the following libraries:
- `HomeSpan` by Gregg
- `Adafruit NeoPixel` by Adafruit

### How to install libraries in the Arduino IDE
1. Open the Library Managaer (located on the left side if using Arduino IDE V2).
2. Search for the library and click install.


## Add support for ESP32
- Install [ESP32 add-on](https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/) in the Arduino IDE.
- If the ESP32 does not appear when selecting the port, you may not have the driver on the PC. Download the [ESP32 drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads). In Windows, you can locate USB accessories in Device Manager, and updating the driver by right clicking on it and update driver. Select manual and locate the downloaded folder. 



## Setup Guide
1. Edit the pin and the number of pixels of the LED strip within the code. 
2. Select boardtype (In my case `Adafruit ESP32 Feather`) and port.
3. Hold in the `boot button` on ESP32 while uploading the code.
4. Open serial monitor and select baud type `115200`.
5. Type "W" to search for available Wifi networks. Select the corrrect network and write in the password.
6. Open the HomeKit app on an Apple device. Click on add accessories and add manually accessories.
7. Enter HomeKit Setup Code `466-37-726` when prompted.

