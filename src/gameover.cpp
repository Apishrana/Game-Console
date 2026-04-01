#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

void printMapGO();
void changeFrame();
void loopGo();

int uiMapGO[8][16] = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
    {0, 3, 3, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {3, 0, 0, 3, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3},
    {0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
};
bool gameOver = true;
int currentframe = 1;

void printMapGO() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if (uiMapGO[i][j] == 1) {
        setOutputColorMap(coordinate, CRGB::Red);
      } else if (uiMapGO[i][j] == 2) {
        setOutputColorMap(coordinate, CRGB::Blue);
      } else if (uiMapGO[i][j] == 3) {
        setOutputColorMap(coordinate, CRGB::White);
      }
    }
  }
}

void changeFrame() {
  if (currentframe == 1) {
    uiMapGO[3][3] = 0;
    uiMapGO[3][12] = 0;
    currentframe = 2;
  } else if (currentframe == 2) {
    uiMapGO[3][3] = 2;
    uiMapGO[3][12] = 2;
    currentframe = 1;
  }
}

void loopGo() {
  if (gameOver) {
    printMapGO();
    changeFrame();
    delay(800);
  }
}