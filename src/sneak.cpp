#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

int getMapPointSNK();
void setMapPointSNK();
void printMapSNK();
void updatePlayerSNK();
void checkDeathSNK();
void spawnAppleSNK();
void startSNK();
void loopSNK();
void playerInputSNK();

int gameMapSNK[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

bool gameOverSNK = false;
Point playerPointsSNK[130] = {{2, 4}, {3, 4}};
int playerLengthSNK = 2;
int playerDirectionSNK = 4;
Point applePosSNK = {7, 4};

int getMapPointSNK(int x, int y) { return gameMapSNK[y][x]; }

void setMapPointSNK(Point pos, int val) { gameMapSNK[pos.y][pos.x] = val; }

void printMapSNK() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if (gameMapSNK[i][j] == 1) {
        setOutputColorMap(coordinate, CRGB::Red);
      } else if (gameMapSNK[i][j] == 2) {
        setOutputColorMap(coordinate, CRGB::Blue);
      }
    }
  }
}

void updatePlayerSNK() {

  // del last block
  setMapPointSNK(playerPointsSNK[0], 0);
  for (int i = 0; i < playerLengthSNK - 1; i++) {
    playerPointsSNK[i] = playerPointsSNK[i + 1];
  }
  playerLengthSNK--;
  // move
  Point headPos = playerPointsSNK[playerLengthSNK - 1];
  switch (playerDirectionSNK) {
  case 1:
    // up
    headPos.y -= 1;
    break;
  case 2:
    // down
    headPos.y += 1;
    break;
  case 3:
    // left
    headPos.x -= 1;
    break;
  case 4:
    // right
    headPos.x += 1;
    break;
  }
  if (headPos.x > 15) {
    headPos.x -= 16;
  } else if (headPos.x < 0) {
    headPos.x += 16;
  }
  if (headPos.y > 7) {
    headPos.y -= 8;
  } else if (headPos.y < 0) {
    headPos.y += 8;
  }
  playerPointsSNK[playerLengthSNK++] = headPos;

  Point headPos2 = playerPointsSNK[playerLengthSNK - 1];

  bool foundApple = false;
  for (int k = 0; k < playerLengthSNK; k++) {
    Point i = playerPointsSNK[k];
    if (i.x == applePosSNK.x && i.y == applePosSNK.y) {
      foundApple = true;
      break;
    }
  }
  if (foundApple) {
    switch (playerDirectionSNK) {
    case 1:
      // up
      headPos2.y -= 1;
      break;
    case 2:
      // down
      headPos2.y += 1;
      break;
    case 3:
      // left
      headPos2.x -= 1;
      break;
    case 4:
      // right
      headPos2.x += 1;
      break;
    }
    if (headPos2.x > 15) {
      headPos2.x -= 16;
    } else if (headPos2.x < 0) {
      headPos2.x += 16;
    }
    if (headPos2.y > 7) {
      headPos2.y -= 8;
    } else if (headPos2.y < 0) {
      headPos2.y += 8;
    }
    playerPointsSNK[playerLengthSNK++] = headPos2;

    spawnAppleSNK();
  }
  for (int k = 0; k < playerLengthSNK; k++) {
    Point i = playerPointsSNK[k];
    setMapPointSNK(i, 1);
  }
}

void checkDeathSNK() {
  for (int i = 0; i < playerLengthSNK; i++) {
    for (int j = i + 1; j < playerLengthSNK; j++) {
      if (playerPointsSNK[i].x == playerPointsSNK[j].x &&
          playerPointsSNK[i].y == playerPointsSNK[j].y) {
        gameOverSNK = true;
      }
    }
  }
}

void spawnAppleSNK() {
  applePosSNK.x = random(0, 15);
  applePosSNK.y = random(0, 7);

  bool conflict = false;
  for (int i = 0; i < playerLengthSNK; i++) {
    if (playerPointsSNK[i].x == applePosSNK.x &&
        playerPointsSNK[i].y == applePosSNK.y) {
      conflict = true;
      break;
    }
  }
  if (conflict) {
    spawnAppleSNK();
  }
  setMapPointSNK(applePosSNK, 2);
}
void playerInputSNK() {
  if (digitalRead(UpbuttonPin)) {
    playerDirectionSNK = 1;
  }
  if (digitalRead(DownbuttonPin)) {
    playerDirectionSNK = 2;
  }
  if (digitalRead(LeftbuttonPin)) {
    playerDirectionSNK = 3;
  }
  if (digitalRead(RightbuttonPin)) {
    playerDirectionSNK = 4;
  }
  int jsH = analogRead(JoystickHPin);
  int jsV = analogRead(JoystickVPin);
  if (jsV < 400) {
    playerDirectionSNK = 1;
  }
  if (jsV > 700) {
    playerDirectionSNK = 2;
  }
  if (jsH < 400) {
    playerDirectionSNK = 3;
  }
  if (jsH > 700) {
    playerDirectionSNK = 4;
  }
}

void startSNK() {

  for (int i = 0; i < playerLengthSNK; i++) {
    setMapPointSNK(playerPointsSNK[i], 1);
  }
  spawnAppleSNK();
}

void loopSNK() {
  if (!gameOverSNK) {
    updatePlayerSNK();
    printMapSNK();
    delay(700);
    playerInputSNK();
    checkDeathSNK();
  } else {
    setScreen('g');
  }
}