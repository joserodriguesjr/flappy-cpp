#pragma once

#include "color.hpp"

#ifdef DESKTOP
#include "raylib.h"

#else
// Image, pixel data stored in CPU memory (RAM)
typedef struct Image {
  void *data;  // Image raw data
  int width;   // Image base width
  int height;  // Image base height
  int mipmaps; // Mipmap levels, 1 by default
  int format;  // Data format (PixelFormat type)
} Image;

// GlyphInfo, font characters glyphs info
typedef struct GlyphInfo {
  int value;    // Character value (Unicode)
  int offsetX;  // Character offset X when drawing
  int offsetY;  // Character offset Y when drawing
  int advanceX; // Character advance position X
  Image image;  // Character image data
} GlyphInfo;

// Texture, tex data stored in GPU memory (VRAM)
typedef struct Texture {
  unsigned int id; // OpenGL texture id
  int width;       // Texture base width
  int height;      // Texture base height
  int mipmaps;     // Mipmap levels, 1 by default
  int format;      // Data format (PixelFormat type)

  Texture() : id(0), width(0), height(0), mipmaps(0), format(0) {}
} Texture;

// Texture2D, same as Texture
typedef Texture Texture2D;

// Vector2, 2 components
typedef struct Vector2 {
  float x; // Vector x component
  float y; // Vector y component
} Vector2;

// Rectangle, 4 components
typedef struct Rectangle {
  float x;      // Rectangle top-left corner position x
  float y;      // Rectangle top-left corner position y
  float width;  // Rectangle width
  float height; // Rectangle height
} Rectangle;

// Font, font texture and GlyphInfo array data
typedef struct Font {
  int baseSize;      // Base size (default chars height)
  int glyphCount;    // Number of glyph characters
  int glyphPadding;  // Padding around the glyph characters
  Texture2D texture; // Texture atlas containing the glyphs
  Rectangle *recs;   // Rectangles in texture for the glyphs
  GlyphInfo *glyphs; // Glyphs info data

  Font()
      : baseSize(0), glyphCount(0), glyphPadding(0), texture(), recs(nullptr),
        glyphs(nullptr) {}
} Font;

#endif

class Renderer {
public:
  static Renderer &instance();
  virtual ~Renderer(){};

  virtual void init(int width, int height) = 0;
  virtual void clear() = 0;
  virtual void draw() = 0;
  virtual void close() = 0;

  virtual int getScreenHeight(void) = 0;
  virtual int getScreenWidth(void) = 0;

  // Get a random value between min and max (both included)
  virtual int getRandomValue(int min, int max) = 0;

  virtual Texture2D loadTexture2D(const char *texturePath) = 0;
  virtual void unloadTexture2D(Texture2D texture) = 0;

  virtual Image loadNewImage(const char *fileName) = 0;
  virtual void unloadImage(Image image) = 0;

  virtual Image cropImage(Image image, Rectangle rec) = 0;
  virtual Texture2D loadTexture2DFromImage(Image image) = 0;

  virtual void setFPS(int fps) = 0;
  virtual float getDeltaTime() = 0;

  // Texture drawing functions

  // Draw a Texture2D
  virtual void drawTexture(Texture2D texture, int posX, int posY,
                           Tint tint) = 0;
  // Draw a Texture2D with extended parameters
  virtual void drawTextureEx(Texture2D texture, Vector2 position,
                             float rotation, float scale, Tint tint) = 0;
  // Draw a part of a texture defined by a rectangle
  virtual void drawTextureRec(Texture2D texture, Rectangle source,
                              Vector2 position, Tint tint) = 0;
  // Draw a part of a texture defined by a rectangle with 'pro' parameters
  virtual void drawTexturePro(Texture2D texture, Rectangle source,
                              Rectangle dest, Vector2 origin, float rotation,
                              Tint tint) = 0;

  // Draw a color-filled rectangle
  virtual void drawRectangle(int posX, int posY, int width, int height,
                             Tint tint) = 0;
  // Draw a color-filled rectangle
  virtual void drawRectangleRec(Rectangle rec, Tint tint) = 0;

  // Text drawing functions

  // Draw text (using default font)
  virtual void drawText(const char *text, int posX, int posY, int fontSize,
                        Tint tint) = 0;
  // Measure string width for default font
  virtual int measureText(const char *text, int fontSize) = 0;

  // Check collision between two rectangles
  virtual bool checkCollisionRecs(Rectangle rec1, Rectangle rec2) = 0;
};
