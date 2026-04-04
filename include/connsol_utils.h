#pragma once

struct Point {
  int x;
  int y;
};
struct CharBitmap {
  char key;
  int width;
  int bitmap[5][5];
};

inline bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const Point &a, const Point &b) { return !(a == b); }

void setOutputColorMap(int coordinate[2], CRGB color);
void setScreen(char c);

extern int UpbuttonPin;
extern int DownbuttonPin;
extern int LeftbuttonPin;
extern int RightbuttonPin;
extern int JoystickBtnPin;
extern int JoystickHPin;
extern int JoystickVPin;