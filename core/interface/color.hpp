#pragma once

#ifdef DESKTOP
#include "raylib.h"

#define LIGHT_GREEN                                                            \
  CLITERAL(Color) { 0, 228, 48, 100 }

#define LIGHT_BLACK                                                            \
  CLITERAL(Color) { 0, 0, 0, 100 }

#else
typedef struct Color {
  unsigned char r; // Color red value
  unsigned char g; // Color green value
  unsigned char b; // Color blue value
  unsigned char a; // Color alpha value
} Color;

#define WHITE 0xffff
#define LIGHT_GREEN 0x07E0
#define LIGHT_BLACK 0x0000

#endif

enum class TintType { COLOR, HEX };

class Tint {
public:
  TintType type;
  union {
    Color color;
    unsigned int hexValue;
  };

  Tint(Color c) : type(TintType::COLOR), color(c) {}
  Tint(unsigned int h) : type(TintType::HEX), hexValue(h) {}
};