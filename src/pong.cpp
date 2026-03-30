#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

void setMapPointPong();
void printMapPong();
void playerSetupPong();
void updateBallPong();
void movePl1();
void movePl2();
void loopPong();
void setupPong();
void playerScorePong(int player);
void displayScore();

int gameMapPong[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

bool gameOverPong = false;
int pl1[3][2] = {{1, 3}, {1, 4}, {1, 5}};
int pl2[3][2] = {{14, 3}, {14, 4}, {14, 5}};
int pl1Score = 0;
int pl2Score = 0;
int ballPosList[4][2] = {{8, 4}, {7, 4}, {8, 3}, {7, 3}};
int ballVelList[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
int ballPos[2];
int ballVelocity[2];

void setMapPointPong(int pos[2], int val) { gameMapPong[pos[1]][pos[0]] = val; }

void printMapPong() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if (gameMapPong[i][j] == 3) {
        setOutputColorMap(coordinate, CRGB::Red);
      } else if (gameMapPong[i][j] == 2) {
        setOutputColorMap(coordinate, CRGB::Blue);
      } else if (gameMapPong[i][j] == 9) {
        setOutputColorMap(coordinate, 0xff6600);
      } else if (gameMapPong[i][j] == 8) {
        setOutputColorMap(coordinate, 0x3399ff);
      } else if (gameMapPong[i][j] == 1) {
        setOutputColorMap(coordinate, CRGB::Green);
      }
    }
  }
}

void playerSetupPong() {
  for (int (&i)[2] : pl1) {
    setMapPointPong(i, 2);
  }
  for (int (&i)[2] : pl2) {
    setMapPointPong(i, 3);
  }
}

void updateBallPong() {
  int nextBallPos[2] = {ballPos[0] + ballVelocity[0],
                        ballPos[1] + ballVelocity[1]};
  for (int (&i)[2] : pl1) {
    if (i == nextBallPos) {
      ballVelocity[0] = 1;
      break;
    }
  }
  for (int (&i)[2] : pl2) {
    if (i == nextBallPos) {
      ballVelocity[0] = 1;
      break;
    }
  }
  setMapPointPong(ballPos, 0);
  ballPos[0] += ballVelocity[0];
  ballPos[1] += ballVelocity[1];
  setMapPointPong(ballPos, 1);
  if (ballPos[0] >= 15) {
    playerScorePong(1);
    return;
  }
  if (ballPos[0] <= 0) {
    playerScorePong(2);
    return;
  }
  if (ballPos[1] == 7) {
    ballVelocity[1] = -1;
  }
  if (ballPos[1] == 1) {
    ballVelocity[1] = 1;
  }
}

void movePl1(char dir) {
  for (int (&i)[2] : pl1) {
    setMapPointPong(i, 0);
  }
  if (dir == 'u' && pl1[2][1] != 7) {
    for (int i; i < 4; i++) {
      pl1[i][1] += 1;
    }
  } else if (dir == 'd' && pl1[0][1] != 0) {
    for (int i; i < 4; i++) {
      pl1[i][1] -= 1;
    }
  }
}

void movePl2(char dir) {
  for (int (&i)[2] : pl2) {
    setMapPointPong(i, 0);
  }
  if (dir == 'u' && pl2[2][1] != 7) {
    for (int i; i < 4; i++) {
      pl2[i][1] += 1;
    }
  } else if (dir == 'd' && pl2[0][1] != 0) {
    for (int i; i < 4; i++) {
      pl2[i][1] -= 1;
    }
  }
}
void setupPong() {
  int randBallIndex = random(0, 3);
  setMapPointPong(ballPos, 0);
  ballPos[0] = ballPosList[randBallIndex][0];
  ballPos[1] = ballPosList[randBallIndex][1];
  ballVelocity[0] = ballVelList[randBallIndex][0];
  ballVelocity[1] = ballVelList[randBallIndex][1];
  setMapPointPong(ballPos, 1);
}

void playerScorePong(int player) {
  if (player == 1) {
    pl1Score += 1;
  }
  if (player == 2) {
    pl2Score += 1;
  }
  setupPong();
  displayScore();
  if (pl1Score == 9) {
    gameOverPong = true;
  }
  if (pl2Score == 9) {
    gameOverPong = true;
  }
}
void displayScore() {
  for (int i; i < pl1Score; i++) {
    int x[2] = {i, 0};
    setMapPointPong(x, 9);
  }
  for (int i; i < pl2Score; i++) {
    int x[2] = {15 - i, 0};
    setMapPointPong(x, 8);
  }
}

void loopPong() {
  if (gameOverPong) {
    playerSetupPong();
    updateBallPong();
    printMapPong();
    delay(700);

    if (digitalRead(UpbuttonPin)) {
      movePl1('u');
    }
    if (digitalRead(DownbuttonPin)) {
      movePl1('d');
    }
    int jsV = analogRead(JoystickVPin);
    if (jsV < 400) {
      movePl2('u');
    }
    if (jsV > 700) {
      movePl2('d');
    }
  } else {
    setScreen('g');
  }
}