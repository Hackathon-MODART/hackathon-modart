#include <FastLED.h>

#define LED_PIN     13
#define WIDTH       32
#define HEIGHT      16
#define NUM_LEDS    (WIDTH * HEIGHT)
#define BRIGHTNESS  40
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define PANEL_HEIGHT 8
#define PANEL_LED_COUNT 256

CRGB leds[NUM_LEDS];

uint16_t XY(uint8_t x, uint8_t y) {
  uint16_t returnValue;
  
  if (y < PANEL_HEIGHT) {
    // Bas de l'affichage = panneau du bas (1er dans la chaîne)
    if (x % 2 == 0) {
      returnValue = (x * PANEL_HEIGHT) + PANEL_HEIGHT - 1 - y;
    } else {
      returnValue = (x * PANEL_HEIGHT) + y ;
    }
  } else {
    // Haut de l'affichage = panneau du haut (2e dans la chaîne)
     if (x % 2 == 0) {
      returnValue = (31 - x) * PANEL_HEIGHT + PANEL_LED_COUNT + HEIGHT - y - 1;
     } else {
      returnValue = (30 - x) * PANEL_HEIGHT + PANEL_LED_COUNT + y;
     }
  }

  Serial.println("x:");
  Serial.println(x);
  Serial.println("y:");
  Serial.println(y);
  Serial.println("return value:");
  Serial.println(returnValue);

  return returnValue;
}

void setup() {
  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  FastLED.clear();
  
  leds[XY(0, 0)]   = CRGB::Red;    // bas gauche
  leds[XY(31, 0)]  = CRGB::Green;  // bas droit

  //leds[XY(0,8)] = CRGB::White;
  //leds[XY(1,8)] = CRGB::White;
  //leds[XY(2,8)] = CRGB::White;

  leds[XY(31,8)] = CRGB::White;
  leds[XY(0,8)] = CRGB::White;
  //leds[256] = CRGB::White;
  //leds[264] = CRGB::White;
  //leds[503] = CRGB::White;


  leds[XY(0, 15)]  = CRGB::Blue;   // haut gauche
  leds[XY(31, 15)] = CRGB::White;  // haut droit


  FastLED.show();
  delay(1000);
}