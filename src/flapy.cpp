#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

void pushPipe();
void spawnPipe();
void printMapFB();
void playerCheck();
int getMapPoint(int x, int y);
void setMapPoint(int posX, int posY, int val);

int gameMapFB[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int pipes[5][8] = {
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
int frameCounter = 0;
int playerX = 2;
int playerY = 4;

bool gameOver = false;

bool buttonVal;

void spawnPipe() {
  int pipe[8];
  int randNo = random(0, 4);
  for (int i = 0; i < 8; i++) {
    pipe[i] = pipes[randNo][i];
  };
  for (int i = 0; i < 8; i++) {
    setMapPoint(15, i, pipe[i]);
  };
}

void pushPipe() {
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

int getMapPoint(int x, int y) { return gameMapFB[y][x]; };

void setMapPoint(int posX, int posY, int val) { gameMapFB[posY][posX] = val; };

void playerCheck() {
  if (playerY > 7 || getMapPoint(playerX, playerY) == 1) {
    gameOver = true;
  };
}

void printMapFB() {

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if ((j == playerX) && (i == playerY)) {
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

void FBloop() {
  buttonVal = digitalRead(UpbuttonPin) || digitalRead(DownbuttonPin) ||
              digitalRead(LeftbuttonPin) || digitalRead(RightbuttonPin) ||
              digitalRead(JoystickBtnPin) || digitalRead(JoystickHPin) ||
              digitalRead(JoystickVPin);
  if (!gameOver) {
    pushPipe();
    if (frameCounter == 0) {
      spawnPipe();
      frameCounter = 4;
    }
    printMapFB();
    delay(700);
    frameCounter -= 1;
    playerY += 1;
    playerCheck();
    if (buttonVal) {
      playerY -= 2;
    }
  } else {
    setScreen('g');
  }
}