#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

// Digital IO pin connected to the button. This will be driven with a
// pull-up resistor so the switch pulls the pin to ground momentarily.
// On a high -> low transition the button press logic will execute.
#define BUTTON_PIN   4

#define PIXEL_PIN    2  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 25  // Number of NeoPixels


Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


boolean oldState = HIGH;
int mode = 0;

int dir = 1;
int bright = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); 
}

void loop() {
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);


  if((newState == LOW) && (oldState == HIGH)) {
    delay(20);
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      
      if(++mode > 10) mode = 0; 
      switch(mode) {           
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;          
        case 1:
          strip.fill(strip.Color(51,195,247),0); // Arc Reactor Blue
          strip.show();
          break;
        case 2:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 3:
          strip.fill(strip.Color(103,199,235),0); // Arc Reactor Blue (Maya Blue)
          strip.show();
          break;
        case 4:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 5:
          strip.fill(strip.Color(127,127,127),0); //White
          strip.show();
          break;
        case 6:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
                 
        case 7:
          pulse(strip.Color(51,195,247),15); // Pulsing Arc Reactor Blue
          break;        
        case 8:
          pulse(strip.Color(103,199,235),15); // Pulsing Arc Reactor Blue (other)
          break;
        case 9:
           pulse(strip.Color(127, 127, 127), 10); // Pulsing White
          break;  
        case 10:
          rainbow(10);
          break;
      }
    }
  }
  oldState = newState;
}

void pulse(uint32_t color, int wait) {
  delay(1000); // To avoid double click such that checkState is LOW right away.
  
  boolean continuePulsing = true;
  while (continuePulsing) {
   
      //fading up
    for (int brightness = 0; brightness < 255; brightness++) {
      boolean checkState = digitalRead(BUTTON_PIN);
      if (checkState == LOW) {
        continuePulsing = false;
        break;
      }
      strip.fill(color,0);
      strip.setBrightness(brightness);
      strip.show();
      delay(wait);
    }
    delay(150);

    if (continuePulsing == false) {
      break;
    }
    
      //fading down
    for (int brightness = 255; brightness > 0; brightness--) {
      boolean checkState = digitalRead(BUTTON_PIN);
      if (checkState == LOW) {
        continuePulsing = false;
        break;
      }
      strip.fill(color,0);
      strip.setBrightness(brightness);
      strip.show();
      delay(wait);
    }
    delay(150);
  }
  colorWipe(strip.Color(  0,   0,   0), 50);
}



// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}



// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
