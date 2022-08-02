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

const int roll = 18;
const int pitch = 19;

// TODO: Find out what digital pins to use for the different buttons.
// TODO: Find out what analog pins to use for roll and pitch.

// Last state of the buttons
int lastButtonState[12] = {0,0,0, 0,0,0, 0,0,0, 0,0,0}; 

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
    pinMode(select, INPUT_PULLUP); // ? Do we need to rename this variable? Is it a protected name in C++/Arduino?

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


    // ? Should the range be set, and if so, to what?
    Joystick.setRxAxisRange(-512, 512); 
    Joystick.setRyAxisRange(-512, 512);
}


void loop() {

    gamepad(); // Reading pin values for the gamepad.
    
    buttons(); // Reading pin values for the buttons.
	
    // ? Is this the right way? Seen multiple ways of doing this.
    int rollValue = analogRead(roll);
    rollValue = map(rollValue, 0, 1023, 0, 255);
    Joystick.setRxAxis(rollValue);

    int pitchValue = analogRead(pitch);
    pitchValue = map(pitchValue, 0, 1023, 0, 255);
    Joystick.setRxAxis(pitchValue);

    delay(10); // TODO: Find the right amount of delay needed.
}

/**
 * @brief Goes through each of the buttons on the flight yoke and checks if the states of the buttons has changed.
 * Buttons: 6-12 
 * Indexes: 5-11 
 * Pins: 7-13
 * 
 */
void buttons() {
    for (int buttonIndex = 5; buttonIndex < 12; buttonIndex++) {
        int currentButtonState = !digitalRead(buttonIndex + 2);

        if (currentButtonState != lastButtonState[buttonIndex]) {
            Joystick.setButton(buttonIndex, currentButtonState);
            lastButtonState[buttonIndex] = currentButtonState;
        }
    }
}


/**
 * @brief Goes through each of the buttons on the gamepad and checks if the state of the buttons has changed.
 * Updates the X and Y axis according to the button states.
 */
void gamepad() {
  // Read pin values
    for (int buttonIndex = 0; buttonIndex < 5; buttonIndex++) {
        int currentButtonState = !digitalRead(buttonIndex + 2);
        if (currentButtonState != lastButtonState[buttonIndex]) {
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
        lastButtonState[buttonIndex] = currentButtonState;
        }
    }
}
