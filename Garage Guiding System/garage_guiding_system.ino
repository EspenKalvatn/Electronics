/**
 * @file garage_guiding_system.ino
 * @author Espen Kalvatn (espen.kalvatn@hotmail.com)
 * @brief Code for a distance sensor (HC-SR04) planned for using in a garage to help guide 
 * a car by displaying different number of LEDs in different colors depending on 
 * how close the car is from the sensor. The LED list for this code consists of 30 individual LEDs.
 * @version 1.0
 * @date 2022-08-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif


#define ECHO_PIN 2
#define TRIG_PIN 3
#define PIXEL_PIN 4

#define PIXEL_COUNT 30

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

long duration;
int distance;

int currentState;
int lastState = 0;

int numberOfBlinks = 0;


void setup() {
    pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an INPUT

    strip.begin();
    strip.show(); 

    Serial.begin(9600); // For displaying the distances in the Serial window (Ctrl + Shift + M in the Arduino IDE).
}


void loop() {
    // This is meant for stoping the arduino after the car has parked (after 50 consecutive blinks).
    if (numberOfBlinks >= 50) {
        setAllLeds(0, 0, 0, PIXEL_COUNT);
        exit(0);
    }

    distance = measureDistance(); // Measuring the distance.
    currentState = getCurrentState(distance); // Evaluating which state it is in.

    // The car is at the stoping point. The lights are blinking.
    if (currentState == 0) {
        blink(255,0,0,100);
        numberOfBlinks++; // Counting the amount of consecutive blinks.
    } 
    else if (currentState != lastState) {
        setLights(currentState);

        // For testing purposes (displaying the distances in the Serial window).
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        Serial.print("State: ");
        Serial.println(currentState);

        Serial.println(" ");
        // ---------------------------------

        lastState = currentState; // Updating the last state.
        numberOfBlinks = 0; // Resetting the number of blinks.
    }

    delay(100);
}


/**
 * @brief This method is measuring the distance from the sensor to an object by emitting an ultrasound 
 * which travels through the air, and if there is an object or obstacle on its path, It will bounce back 
 * to the module. Considering the travel time and the speed of the sound, we can calculate the distance.
 * 
 * @return int - the distance measured in centimeters.
 */
int measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}


/**
 * @brief This method gets the current state of a object based on the distance provided.
 * The LED-list has 30 individual LEDs and this method maps the distance provided to a state between 0 and 29.
 * 
 * State 0: 35 cm from the sensor (minimum).
 * State 29: 335 cm from the sensor (maximum).
 * 
 * It is 10 cm between each state.
 * 
 * @param distance the distance (in centimeters).
 * @return int - the state of the object (0-29).
 */
int getCurrentState(int distance) {
    for (int i = 35; i < 335; i += 10) {
        if (distance < i) {
            return (i - 35) / 10;
        }
    }
    return 29;
}


/**
 * @brief Lights up a number of LEDs based on the provided state. 
 * Closer an object gets, the more LEDs will light up.  
 * 
 * LEDs 1-10 will light up green.
 * LEDs 11-20 will light up orange.
 * LEDs 21-30 will light up red. 
 * 
 * @param state the state of the object (0-29).
 */
void setLights(int state) {
    setAllLeds(0, 0, 0, PIXEL_COUNT);

    if (state == 29) {
        // No lights should be on (distance is larger than the maximum length set).
    } else if (state > 19) {
        setAllLedsBetween(0, 255, 0, 0, 30 - state); // Only lights up a number of green LEDs. (30-state)
    } else if (state > 9) {
        setAllLedsBetween(0, 255, 0, 0,10); // Lights up all green LEDs.
        setAllLedsBetween(255, 165, 0, 10, 30 - state); // Only lights up a number of orange LEDs. (30-state)
    } else {
        setAllLedsBetween(0, 255, 0, 0,10); // Lights up all green LEDs.
        setAllLedsBetween(255, 165, 0, 10,20); // Lights up all orange LEDs.
        setAllLedsBetween(255, 0, 0, 20, 30 - state); // Only lights up a number of red LEDs. (30-state)
    }

    strip.show();
}


/**
 * @brief This method makes a blink effect by turning all the LEDs off, 
 * and then on again with a specified color and delay.
 * 
 * @param red the RGB value of red.
 * @param green the RGB value of green.
 * @param blue the RGB value of blue.
 * @param delay how much delay you want between the blinks.
 */
void blink(byte red, byte green, byte blue, int delay) {
    setAllLeds(0, 0, 0, PIXEL_COUNT);
    delay(delay);
    setAllLeds(red, green, blue, PIXEL_COUNT);
    delay(delay);
}


/**
 * @brief Set all LEDs from a start pixel to an end pixel to a specified color.
 * 
 * @param red the RGB value of red.
 * @param green the RGB value of green.
 * @param blue the RGB value of blue.
 * @param start the pixel to start from.
 * @param end the pixl to go to.
 */
void setAllLedsBetween(byte red, byte green, byte blue, int start, int end) {
  for (int i = start; i < end; i++ ) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}


/**
 * @brief Set all LEDs to a specified color.
 * 
 * @param red the RGB value of red.
 * @param green the RGB value of green.
 * @param blue the RGB value of blue.
 * @param numberOfPixels the number of LEDs to the LED-list.
 */
void setAllLeds(byte red, byte green, byte blue, numberOfPixels) {
    setAllLedsBetween(red, green, blue, 0, numberOfPixels);
}