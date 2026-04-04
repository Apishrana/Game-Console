#include <Arduino.h>
#include <FastLED.h>
#include <connsol_utils.h>

void printUiMM();
void FillUiTextBuffer(char text[]);
void buildIcons();
void renderIcons();
void loopMM();

CharBitmap bitmap[36] = {
    {'a',
     4,
     {
         {0, 1, 1, 0},
         {1, 0, 0, 1},
         {1, 1, 1, 1},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
     }},
    {'b',
     3,
     {
         {1, 1, 0},
         {1, 0, 1},
         {1, 1, 0},
         {1, 0, 1},
         {1, 1, 0},
     }},
    {'c',
     3,
     {
         {0, 1, 1},
         {1, 0, 0},
         {1, 0, 0},
         {1, 0, 0},
         {0, 1, 1},
     }},
    {'d',
     3,
     {
         {1, 1, 0},
         {1, 0, 1},
         {1, 0, 1},
         {1, 0, 1},
         {1, 1, 0},
     }},
    {'e',
     3,
     {
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
     }},
    {'f',
     3,
     {
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 0},
         {1, 0, 0},
         {1, 0, 0},
     }},
    {'g',
     5,
     {
         {0, 1, 1, 1, 1},
         {1, 0, 0, 0, 0},
         {1, 0, 0, 1, 0},
         {1, 0, 0, 0, 1},
         {0, 1, 1, 1, 0},
     }},
    {'h',
     3,
     {
         {1, 0, 1},
         {1, 0, 1},
         {1, 1, 1},
         {1, 0, 1},
         {1, 0, 1},
     }},
    {'i',
     3,
     {
         {1, 1, 1},
         {0, 1, 0},
         {0, 1, 0},
         {0, 1, 0},
         {1, 1, 1},
     }},
    {'j',
     4,
     {
         {1, 1, 1, 1},
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {1, 0, 1, 0},
         {0, 1, 1, 0},
     }},
    {'k',
     4,
     {
         {1, 0, 0, 1},
         {1, 0, 1, 0},
         {1, 1, 0, 0},
         {1, 0, 1, 0},
         {1, 0, 0, 1},
     }},
    {'l',
     3,
     {
         {1, 0, 0},
         {1, 0, 0},
         {1, 0, 0},
         {1, 0, 0},
         {1, 1, 1},
     }},
    {'m',
     5,
     {
         {1, 0, 0, 0, 1},
         {1, 1, 0, 1, 1},
         {1, 0, 1, 0, 1},
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
     }},
    {'n',
     5,
     {
         {1, 0, 0, 0, 1},
         {1, 1, 0, 0, 1},
         {1, 0, 1, 0, 1},
         {1, 0, 0, 1, 1},
         {1, 0, 0, 0, 1},
     }},
    {'o',
     4,
     {
         {0, 1, 1, 0},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {0, 1, 1, 0},
     }},
    {'p',
     3,
     {
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
         {1, 0, 0},
         {1, 0, 0},
     }},
    {'q',
     4,
     {
         {0, 1, 1, 0},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {1, 0, 1, 0},
         {0, 1, 0, 1},
     }},
    {'r',
     4,
     {
         {1, 1, 1, 0},
         {1, 0, 0, 1},
         {1, 1, 1, 1},
         {1, 0, 1, 0},
         {1, 0, 0, 1},
     }},
    {'s',
     3,
     {
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
     }},
    {'t',
     3,
     {
         {1, 1, 1},
         {0, 1, 0},
         {0, 1, 0},
         {0, 1, 0},
         {0, 1, 0},
     }},
    {'u',
     4,
     {
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {1, 0, 0, 1},
         {0, 1, 1, 0},
     }},
    {'v',
     5,
     {
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {0, 1, 0, 1, 0},
         {0, 0, 1, 0, 0},
     }},
    {'w',
     5,
     {
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {1, 1, 0, 1, 1},
         {1, 0, 1, 0, 1},
     }},
    {'x', 3, {{1, 0, 1}, {1, 0, 1}, {0, 1, 0}, {1, 0, 1}, {1, 0, 1}}},
    {'y',
     3,
     {
         {1, 0, 1},
         {1, 0, 1},
         {1, 0, 1},
         {0, 1, 0},
         {0, 1, 0},
     }},
    {'z',
     3,
     {
         {1, 1, 1},
         {0, 0, 1},
         {0, 1, 0},
         {1, 0, 0},
         {1, 1, 1},
     }},
    {'1',
     3,
     {
         {0, 1, 0},
         {1, 1, 0},
         {0, 1, 0},
         {0, 1, 0},
         {1, 1, 1},
     }},
    {'2',
     3,
     {
         {1, 1, 0},
         {0, 0, 1},
         {0, 1, 0},
         {1, 0, 0},
         {1, 1, 1},
     }},
    {'3',
     3,
     {
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
     }},
    {'4',
     3,
     {
         {1, 0, 1},
         {1, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {0, 0, 1},
     }},
    {'5',
     3,
     {
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
     }},
    {'6',
     3,
     {
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
     }},
    {'7',
     4,
     {
         {1, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 1, 1, 1},
         {0, 0, 1, 0},
         {0, 0, 1, 0},
     }},
    {'8',
     3,
     {
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
     }},
    {'9',
     3,
     {
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {0, 0, 1},
     }},
    {'0',
     3,
     {
         {1, 1, 1},
         {1, 0, 1},
         {1, 0, 1},
         {1, 0, 1},
         {1, 1, 1},
     }},
};

int uiMapMM[8][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int uiBufferMM[8][255];
int gameIconRowMM[3][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int offsetMM = 0;
int uiBufferWidthMM = 0;
int frameMM = 0;
int blinkFrameMM = 4;
int blinkOnMM = true;
int selectedIconIndexMM = 1;
bool inMainMenu = true;

void printUiMM() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int coordinate[2] = {i, j};
      if (uiMapMM[i][j] == 1) {
        setOutputColorMap(coordinate, CRGB::White);
      } else if (uiMapMM[i][j] == 2) {
        setOutputColorMap(coordinate, CRGB::Blue);
      }
      //   else if (uiMapMM[i][j] == 3) {
      //     setOutputColorMap(coordinate, CRGB::Red);
      //   } else if (uiMapMM[i][j] == 4) {
      //     setOutputColorMap(coordinate, CRGB::Red);
      //   } else if (uiMapMM[i][j] == 5) {
      //     setOutputColorMap(coordinate, CRGB::Red);
      //   } else if (uiMapMM[i][j] == 6) {
      //     setOutputColorMap(coordinate, CRGB::Red);
      //   }
    }
  }
};

void FillUiTextBuffer(char text[]) {
  memset(uiBufferMM, 0, sizeof(uiBufferMM));
  int bufferIndex = 0;
  for (int j = 0; j < 3; j++) {
    for (int i; i < 5; i++) {
      uiBufferMM[j][i] = 0;
    }
  };
  bufferIndex += 3;
  int textLen = sizeof(text);
  for (int t = 0; t > textLen; t++) {
    CharBitmap bm;
    for (CharBitmap b : bitmap) {
      if (b.key == text[t]) {
        bm = b;
        break;
      }
    }

    for (int i = 0; i < bm.width; i++) {
      for (int j = 0; j < 5; j++) {
        uiBufferMM[bufferIndex][j] = bm.bitmap[j][i];
      }
      bufferIndex++;
    }

    for (int j; j < 5; j++) {
      uiBufferMM[bufferIndex][j] = 0;
    }
    bufferIndex++;
  }

  for (int j = bufferIndex; j < bufferIndex + 2; j++) {
    for (int i; i < 5; i++) {
      uiBufferMM[j][i] = 0;
    }
  };
  uiBufferWidthMM = sizeof(uiBufferMM);
};

void buildIcons() {
  memset(gameIconRowMM, 0, sizeof(gameIconRowMM));

  for (int i = 0; i < 4; i++) {
    if (i == selectedIconIndexMM) {
      if (blinkOnMM) {
        for (int y = 0; y < 3; y++) {
          for (int x = 0; x < 3; x++) {
            gameIconRowMM[y][i * 3 + 2 + x] = 2;
          }
        }
      }
      gameIconRowMM[1][i * 3 + 3] = i + 3;
    } else {
      gameIconRowMM[1][i * 3 + 3] = i + 3;
    }
  }
}

void renderIcons() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uiMapMM[i][j] = gameIconRowMM[i][j];
    }
  }
}

// void setupMM() { FillUiTextBuffer("apish"); }

void loopMM() {

  if (inMainMenu) {
    if (frameMM == blinkFrameMM - 1) {
      blinkOnMM = not blinkOnMM;
    }
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 5; j++) {
        uiMapMM[j + 3][i] = uiBufferMM[(offsetMM + i) % uiBufferWidthMM][j];
      }
    }
    buildIcons();
    renderIcons();
    printUiMM();
    delay(0.25);
    offsetMM = (offsetMM + 1) % uiBufferWidthMM;
    frameMM = (frameMM + 1) % blinkFrameMM;
  } else {
  }
}