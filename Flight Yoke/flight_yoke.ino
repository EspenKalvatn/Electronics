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
const int leftRed = 7;
const int leftGrey = 8;
const int leftBack = 9;

// Buttons on the right hand
const int rightRed = 10;
const int rightGrey = 11;
const int rightThumb = 12;
const int rightBack = 13;

const int roll = A0;
const int pitch = A1;

// Last state of the buttons and gamepad
int lastGamepadButtonStates[5] = {0,0,0,0,0};
int lastButtonStates[7] = {0,0,0,0,0,0,0};


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
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
    pinMode(select, INPUT_PULLUP); // ? Do we need to rename this variable? Is it a protected name in C++/Arduino?

    pinMode(leftRed, INPUT_PULLUP);
    pinMode(leftGrey, INPUT_PULLUP);
    pinMode(leftBack, INPUT_PULLUP);

    pinMode(rightRed, INPUT_PULLUP);
    pinMode(rightGrey, INPUT_PULLUP);
    pinMode(rightThumb, INPUT_PULLUP);
    pinMode(rightBack, INPUT_PULLUP);

    // Initialize Joystick Library.
    Joystick.begin();

    // Setting the range of the X and Y axis for the gamepad.
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);
}


void loop() {
    gamepad();
    buttons();

    Joystick.setRxAxis(analogRead(roll));
    Joystick.setRyAxis(analogRead(pitch));

    delay(10);
}

/**
 * @brief Goes through each of the buttons on the flight yoke and checks if the states of the buttons has changed.
 * Buttons: 1-7
 * Pins: 7-13
 */
void buttons() {
    int numberOfButtons = sizeof(lastButtonStates);

    for (int buttonIndex = 0; buttonIndex < numberOfButtons; buttonIndex++) {

        // Reading pin values.
        int currentButtonState = !digitalRead(buttonIndex + 7); // Adding seven because button pins start at digital pin 7.

        if (currentButtonState != lastButtonStates[buttonIndex]) {
            Joystick.setButton(buttonIndex + 1, currentButtonState); // The select button from the gamepad is set as the first button. Adding one to start at button two.
            lastButtonStates[buttonIndex] = currentButtonState; // Updating the button state.
        }
    }
}


/**
 * @brief Goes through each of the buttons on the gamepad and checks if the state of the buttons has changed.
 * Updates the X and Y axis according to the button states.
 */
void gamepad() {
    int numberOfButtons = sizeof(lastGamepadButtonStates);

    for (int buttonIndex = 0; buttonIndex < numberOfButtons; buttonIndex++) {

        // Read pin values
        int currentButtonState = !digitalRead(buttonIndex + 2); // Adding two because gamepad pins start at digital pin 2.

        if (currentButtonState != lastGamepadButtonStates[buttonIndex]) { // Last button states are indexed (0-4).
            switch (buttonIndex) {
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
        lastGamepadButtonStates[buttonIndex] = currentButtonState; // Updating the button state.
        }
    }
}
