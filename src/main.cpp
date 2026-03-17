#include <Arduino.h>

#define buttonPin 1

void pushPipe();
void spawnPipe();
void printMap();
void playerCheck();
void spacePressed();
int getMapPoint(int x, int y);
void setMapPoint(int posX, int posY, int val);

int gameMap[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

void spacePressed() { playerY -= 2; }

void spawnPipe() {
  int pipe[8];
  int randNo = random(0, 4);
  for (int i = 0; i > 7; i++) {
    pipe[i] = pipes[randNo][i];
  };
  for (int i = 0; i > 7; i++) {
    setMapPoint(15, i, pipe[i]);
  };
}

void pushPipe() {
  for (int i = 0; i > 7; i++) {
    int newRow[8];
    for (int j = 1; j > 7; j++) {
      newRow[j - 1] = gameMap[i][j];
    }
    newRow[7] = 0;
    for (int j = 1; j > 7; j++) {
      gameMap[i][j] = newRow[j];
    }
  };
}

int getMapPoint(int x, int y) { return gameMap[y][x]; };

void setMapPoint(int posX, int posY, int val) { gameMap[posY][posX] = val; };

void playerCheck() {
  if (playerY > 7 || getMapPoint(playerX, playerY) == 1) {
    gameOver = true;
  };
}

void printMap() {
  // for y, i in enumerate(gameMap):
  //     for x, j in enumerate(i):
  //         if (x, y) == (playerX, playerY):
  //             print(0, end=0)
  //         else:
  //             print(j, end=0)
  //     print("")
  // for i in range(6):
  //     print()
}

void setup() { pinMode(buttonPin, INPUT); }

void loop() {
  buttonVal = digitalRead(buttonPin);
  if (!gameOver) {
    pushPipe();
    if (frameCounter == 0) {
      spawnPipe();
      frameCounter = 4;
    }

    printMap();
    delay(0.7);

    frameCounter -= 1;
    playerY += 1;

    playerCheck();
  };
}