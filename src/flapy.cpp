#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

void pushPipeFB();
void spawnPipeFB();
void printMapFB();
void playerCheckFB();
int getMapPointFB(int x, int y);
void setMapPointFB(int posX, int posY, int val);

int gameMapFB[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int pipesFB[5][8] = {
    {
        1,
        0,
        0,
        1,
        1,
        1,
        1,
        1,
    },
    {
        1,
        1,
        0,
        0,
        1,
        1,
        1,
        1,
    },
    {
        1,
        1,
        1,
        0,
        0,
        1,
        1,
        1,
    },
    {
        1,
        1,
        1,
        1,
        0,
        0,
        1,
        1,
    },
    {
        1,
        1,
        1,
        1,
        1,
        0,
        0,
        1,
    },
};
int frameCounterFB = 0;
int playerXFB = 2;
int playerYFB = 4;

bool gameOverFB = false;

bool buttonValFB;

void spawnPipeFB() {
  int pipe[8];
  int randNo = random(0, 4);
  for (int i = 0; i < 8; i++) {
    pipe[i] = pipesFB[randNo][i];
  };
  for (int i = 0; i < 8; i++) {
    setMapPointFB(15, i, pipe[i]);
  };
}

void pushPipeFB() {
  for (int i = 0; i < 8; i++) {
    int newRow[16];
    for (int j = 1; j < 16; j++) {
      newRow[j - 1] = gameMapFB[i][j];
    }
    newRow[15] = 0;
    for (int j = 0; j < 16; j++) {
      gameMapFB[i][j] = newRow[j];
    }
  };
}

int getMapPointFB(int x, int y) { return gameMapFB[y][x]; };

void setMapPointFB(int posX, int posY, int val) {
  gameMapFB[posY][posX] = val;
};

void playerCheckFB() {
  if (playerYFB > 7 || getMapPointFB(playerXFB, playerYFB) == 1) {
    gameOverFB = true;
  };
}

void printMapFB() {

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if ((j == playerXFB) && (i == playerYFB)) {
        setOutputColorMap(coordinate, CRGB::Green);
      } else {
        if (gameMapFB[i][j]) {
          setOutputColorMap(coordinate, CRGB::Red);
        } else {
          setOutputColorMap(coordinate, CRGB::Blue);
        }
      }
    }
  }
}

void loopFB() {
  buttonValFB = digitalRead(UpbuttonPin) || digitalRead(DownbuttonPin) ||
                digitalRead(LeftbuttonPin) || digitalRead(RightbuttonPin) ||
                digitalRead(JoystickBtnPin) || digitalRead(JoystickHPin) ||
                digitalRead(JoystickVPin);
  if (!gameOverFB) {
    pushPipeFB();
    if (frameCounterFB == 0) {
      spawnPipeFB();
      frameCounterFB = 4;
    }
    printMapFB();
    delay(700);
    frameCounterFB -= 1;
    playerYFB += 1;
    playerCheckFB();
    if (buttonValFB) {
      playerYFB -= 2;
    }
  } else {
    setScreen('g');
  }
}