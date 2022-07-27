#include <Servo.h>

Servo servo1;
Servo servo2;


int servo1Pin = 9; // Pin for the servo 1
int servo2Pin = 10; // Pin for the servo 2
int buttonPin = 2; // Pin for the button
int ledPin = 6; // Pin for the LED-eyes

// Open positon for servo1 should be the same as closed position for servo 2 and vice versa.
int openPositionServo1; // The angle of servo 1 in opened position. 
int openPositionServo2; // The angle of servo 2 in opened position
int closedPositionServo1; // The angle of servo 1 in closed position
int closedPositionServo2; // The angle of servo 2 in closed position

bool isOpen; // True if helmet is open, false if helmet is closed


void setup() {
  // Attaching the servos, button and the LED-lights to their designated pins on the arduino
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  openHelmet; // Opens the helmet when the arduino is turned on (starting position)
  isOpen = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(buttonPin);
  delay(10);
  int val2 = digitalRead(buttonPin);

  if (val == val2) {
    if (isOpen) { // opening the helmet if the helmet is closed and the button is pressed
      closeHelmet();
      isOpen = false;
    }
    else {
      openHelmet(); // closing the helmet if the helmet is open and the button is pressed
      isOpen = true;
    }
  }
}


/* 
 * This function should open the helmet and turn of the LED-lights.
 * Logic for servos and LEDs should be implemented here.
 */
void openHelmet() {
  servo1.write(openPositionServo1);
  servo2.write(openPositionServo2);
  lightsOff();
}

/* 
 * This function should close the helmet and turn on the LED-lights.
 * Logic for servos and LEDs should be implemented here.
 */
void closeHelmet() {
  servo1.write(closedPositionServo1);
  servo2.write(closedPositionServo2);
  lightsOn();
}


void lightsOn() {
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(00);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(00);

  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) { // LEDs fading in
    analogWrite(ledPin, fadeValue);
    delay(30);
  }
}


void lightsOff() {
  delay(1000);
  digitalWrite(ledPin, LOW);
}
