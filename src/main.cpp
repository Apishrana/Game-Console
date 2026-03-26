#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

#define NUM_LEDS 128
#define LED_DATA_PIN 11

#define UpbuttonPin 7
#define DownbuttonPin 4
#define LeftbuttonPin 2
#define RightbuttonPin 8
#define JoystickHPin A5
#define JoystickVPin A4
#define JoystickBtnPin A3

CRGB leds[NUM_LEDS];
CRGB outputColorMap[8][16] = {
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black},
    {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
     CRGB::Black}};

char screen = 'h';
void setOutputColorMap(int indices[2], CRGB Color) {
  outputColorMap[indices[0]][indices[1]] = Color;
}
void setScreen(char newScreen) { screen = newScreen; }

void printMap() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      leds[i * 8 + j] = outputColorMap[i][j];
    }
  }
}

void setup() {
  pinMode(UpbuttonPin, INPUT);
  pinMode(DownbuttonPin, INPUT);
  pinMode(LeftbuttonPin, INPUT);
  pinMode(RightbuttonPin, INPUT);
  pinMode(JoystickBtnPin, INPUT);
  pinMode(JoystickHPin, INPUT);
  pinMode(JoystickVPin, INPUT);
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() { printMap(); }