#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

int getMapPointBO(int x, int y);
void setMapPointBO(int pos[2], int val);
void printMapBO();
void playerSetupBO();
void movePlBO(char dir);
void updateBallBO();
void setupBO();
void loopBO();

int gameMapBO[8][16] = {{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
bool gameOverBO = false;
bool ballLaunchedBO = false;
int plPosBO[4][2] = {{6, 7}, {7, 7}, {8, 7}, {9, 7}};
int ballPosListBO[2][2] = {{8, 6}, {7, 6}};
int ballVelListBO[2][2] = {{1, -1}, {-1, -1}};
int ballPosBO[2];
int ballVelocityBO[2];

int getMapPointBO(int x, int y) { return gameMapBO[y][x]; }

void setMapPointBO(int pos[2], int val) { gameMapBO[pos[1]][pos[0]] = val; }

void printMapBO() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if (gameMapBO[i][j] == 3) {
        setOutputColorMap(coordinate, CRGB::Red);
      } else if (gameMapBO[i][j] == 2) {
        setOutputColorMap(coordinate, CRGB::Blue);

      } else if (gameMapBO[i][j] == 1) {
        setOutputColorMap(coordinate, CRGB::White);
      }
    }
  }
}

void playerSetupBO() {
  for (int (&i)[2] : plPosBO) {
    setMapPointBO(i, 1);
  }
}

void movePlBO(char dir) {
  for (int (&i)[2] : plPosBO) {
    setMapPointBO(i, 0);
  };
  if (dir == 'r' and plPosBO[3][0] != 15) {
    for (int i; i < 4; i++) {
      plPosBO[i][0] += 1;
    }
  } else if (dir == 'l' and plPosBO[0][0] != 0) {
    for (int i; i < 4; i++) {
      plPosBO[i][0] -= 1;
    }
  }
  if (!ballLaunchedBO) {
    setMapPointBO(ballPosBO, 0);
    if (dir == 'r' and plPosBO[3][0] != 15) {
      ballPosBO[0] += 1;
    } else if (dir == 'l' and plPosBO[0][0] != 0) {
      ballPosBO[0] -= 1;
    }
  }
}

void updateBallBO() {
  int nextX = ballPosBO[0] + ballVelocityBO[0];
  int nextY = ballPosBO[1] + ballVelocityBO[1];

  if (getMapPointBO(nextX, nextY) == 1) {
    ballVelocityBO[1] = -1;
  }
  if (getMapPointBO(nextX, nextY) == 2) {
    ballVelocityBO[1] = 1;
  }
  if (getMapPointBO(ballPosBO[0], nextY) == 2) {
    int i[2] = {ballPosBO[0], nextY};
    setMapPointBO(i, 0);
  } else {
    int i[2] = {nextX, nextY};
    setMapPointBO(i, 0);
  }
  setMapPointBO(ballPosBO, 0);
  if (ballLaunchedBO) {
    ballPosBO[0] += ballVelocityBO[0];
    ballPosBO[1] += ballVelocityBO[1];
  }
  if (ballPosBO[0] >= 15) {
    ballVelocityBO[0] = -1;
  }
  if (ballPosBO[0] <= 0) {
    ballVelocityBO[0] = 1;
  }
  if (ballPosBO[1] == 0) {
    ballVelocityBO[1] = 1;
  }
  setMapPointBO(ballPosBO, 2);
  if (ballPosBO[1] == 7) {
    gameOverBO = true;
  }
}

void setupBO() {
  int randBallIndex = random(0, 1);
  setMapPointBO(ballPosBO, 2);
  ballPosBO[0] = ballPosListBO[randBallIndex][0];
  ballPosBO[1] = ballPosListBO[randBallIndex][1];
  ballVelocityBO[0] = ballVelListBO[randBallIndex][0];
  ballVelocityBO[1] = ballVelListBO[randBallIndex][1];
  setMapPointBO(ballPosBO, 1);
}

void loopBO() {
  if (!gameOverBO) {
    playerSetupBO();
    updateBallBO();
    printMapBO();
    delay(700);

    if (digitalRead(LeftbuttonPin)) {
      movePlBO('l');
    }
    if (digitalRead(RightbuttonPin)) {
      movePlBO('r');
    }
    int jsH = analogRead(JoystickHPin);
    if (jsH < 400) {
      movePlBO('l');
    }
    if (jsH > 700) {
      movePlBO('r');
    }
    if (digitalRead(UpbuttonPin) || digitalRead(JoystickBtnPin)) {
      ballLaunchedBO = true;
    }
  } else {
    setScreen('g');
  }
}