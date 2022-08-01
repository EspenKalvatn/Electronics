/**
 * @file flight_yoke.ino
 * @author Espen Kalvatn (espen.kalvatn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <Joystick.h>

// Gamepad button pins. (The digital pins 2 - 6 are grounded when they are pressed)
const int up = 2;
const int right = 3;
const int down = 4;
const int left = 5;
const int select = 6;

// Buttons on the left hand
const int leftA = 7;
const int leftB = 8;
const int leftBack = 9;

// Buttons on the right hand
const int rightA = 10;
const int rightB = 11;
const int rightC = 12;
const int rightBack = 13;

// TODO: Find out what digital pins to use for the different buttons.
// TODO: Find out what analog pins to use for roll and pitch.

// Last state of the buttons
int lastButtonState[12] = {0,0,0, 0,0,0, 0,0,0, 0,0,0}; // ? Is this the best way to do this? Should the button number be linked to the button index somehow?


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // Rotation X (Roll), Rotation Y (Pitch), No Roation Z
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


void setup() {

    // Initialize Button Pins
    pinMode(up, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    pinMode(left, INPUT_PULLUP);
    pinMode(select, INPUT_PULLUP);

    pinMode(leftA, INPUT_PULLUP);
    pinMode(leftB, INPUT_PULLUP);
    pinMode(leftBack, INPUT_PULLUP);

    pinMode(rightA, INPUT_PULLUP);
    pinMode(rightB, INPUT_PULLUP);
    pinMode(rightC, INPUT_PULLUP);
    pinMode(rightBack, INPUT_PULLUP);


    // Initialize Joystick Library
    Joystick.begin();
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);

    // ? Add Joystick roll and pitch?
    // TODO: Find out if needed.
}


void loop() {

    // Reading pin values for the gamepad
    gamepad();


    // TODO: Make for-loop to go through each button.
    // TODO: Check what parameter the readButton() method needs.

    // TODO: Add logic for roll and pitch.

    delay(10); // TODO: Find the right amount of delay needed.
}

/**
 * @brief 
 * 
 * @param buttonIndex 
 * @param pinToButtonMap 
 */
void readButton(int buttonIndex, int pinToButtonMap) {
    int currentButtonState = !digitalRead(pinToButtonMap);
	if (currentButtonState != lastButtonState[buttonIndex]) {
	    Joystick.setButton(buttonIndex, currentButtonState);
	    lastButtonState[buttonIndex] = currentButtonState;
	}
}


/**
 * @brief 
 * 
 */
void gamepad() {
  // Read pin values
    for (int index = 0; index < 5; index++) {
        int currentButtonState = !digitalRead(index + 2);
        if (currentButtonState != lastButtonState[index]) {
            switch (index) {
                case 0: // UP
                if (currentButtonState == 1) {
                    Joystick.setYAxis(-1);
                } else {
                    Joystick.setYAxis(0);
                }
                break;
                case 1: // RIGHT
                if (currentButtonState == 1) {
                    Joystick.setXAxis(1);
                } else {
                    Joystick.setXAxis(0);
                }
                break;
                case 2: // DOWN
                if (currentButtonState == 1) {
                    Joystick.setYAxis(1);
                } else {
                    Joystick.setYAxis(0);
                }
                break;
                case 3: // LEFT
                if (currentButtonState == 1) {
                    Joystick.setXAxis(-1);
                } else {
                    Joystick.setXAxis(0);
                }
                break;
                case 4: // SELECT
                Joystick.setButton(0, currentButtonState);
                break;
            }
        lastButtonState[index] = currentButtonState;
        }
    }
}