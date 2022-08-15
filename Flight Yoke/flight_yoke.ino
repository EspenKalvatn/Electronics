/**
 * @file flight_yoke.ino
 * @author Espen Kalvatn (espen.kalvatn@hotmail.com)
 * @brief Code for a DIY flight yoke 3D-printed (https://www.thingiverse.com/thing:4825314), 
 * with roll and pitch, a gamepad (up, down, right, left, select), and some push buttons.  
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <Joystick.h>

// ! As far as I know, the joystickType needs to be set to JOYSTICK_TYPE_GAMEPAD for all components to work.
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
  8, 0,                     // Button Count, Hat Switch Count
  true, true, false,        // X, Y, Z - Axis
  true, true, false,        // Rotation X (Roll), Rotation Y (Pitch), Roation Z
  false, false,             // Rudder, Throttle
  false, false, false);     // Accelerator, Brake, Steering

// Last state of the buttons.
int lastButtonState[12] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
// Maps the index of the buttons in the switch case below to the corresponding pin on the arduino board.
int buttonToPinMap[12] = {2,3,4, 5,6,7, 8,9,10, 11,12,13};


void setup() {

    // Initialize Button Pins
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP); 

    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);

    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);

    // Initialize Joystick Library.
    Joystick.begin();

    // Setting the range of the X and Y axis for the gamepad.
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);
}


void loop() {
    Joystick.setRxAxis(analogRead(A0)); // Roll
    Joystick.setRyAxis(analogRead(A1)); // Pitch

    // Reading pin values for the gamepad/buttons
    for (int buttonIndex = 0; buttonIndex < sizeof(lastButtonState); buttonIndex++) {
        int currentButtonState = !digitalRead(buttonToPinMap[buttonIndex]); // Gets the current state, by using the mapping from the button index to the pin value.
        if (currentButtonState != lastButtonState[buttonIndex]) { // Checks if the current state is different from the last registered state.
            switch (buttonIndex) { // Finds the right button to change (according to the button index).
                case 0: // Up (gamepad)
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(-1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 1: // Right (gamepad)
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
                case 2: // Down (gamepad)
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 3: // Left (gamepad)
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(-1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
                case 4: // Select (gamepad press down)
                    Joystick.setButton(0, currentButtonState);
                    break;
                case 5: // Left Red Button
                    Joystick.setButton(1, currentButtonState);
                    break;
                case 6: // Left Grey Button
                    Joystick.setButton(2, currentButtonState);
                    break;
                case 7: // Left Back Button
                    Joystick.setButton(3, currentButtonState);
                    break;
                case 8: // Right Red Button
                    Joystick.setButton(4, currentButtonState);
                    break;
                case 9: // Right Grey Button
                    Joystick.setButton(5, currentButtonState);
                    break;
                case 10: // Right Thumb Button
                    Joystick.setButton(6, currentButtonState);
                    break;
                case 11: // Right Back Button
                    Joystick.setButton(7, currentButtonState);
                    break;
            }
        lastButtonState[buttonIndex] = currentButtonState; // Updating the button state.
        }
    }
    delay(10);
}

