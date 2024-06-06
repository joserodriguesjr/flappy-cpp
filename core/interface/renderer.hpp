#pragma once

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
} Font;

// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
  unsigned char r; // Color red value
  unsigned char g; // Color green value
  unsigned char b; // Color blue value
  unsigned char a; // Color alpha value
} Color;

#define WHITE                                                                  \
  CLITERAL(Color) { 255, 255, 255, 255 } // White
#define BLACK                                                                  \
  CLITERAL(Color) { 0, 0, 0, 255 } // Black
#define BLANK                                                                  \
  CLITERAL(Color) { 0, 0, 0, 0 } // Blank (Transparent)
#define MAGENTA                                                                \
  CLITERAL(Color) { 255, 0, 255, 255 } // Magenta
#define RAYWHITE                                                               \
  CLITERAL(Color) { 245, 245, 245, 255 } // My own White (raylib logo)
#define GREEN                                                                  \
  CLITERAL(Color) { 0, 228, 48, 255 } // Green
#endif

class Renderer {
public:
  static Renderer &instance();

  virtual void Init(int width, int height) = 0;
  virtual void Clear() = 0;
  virtual void Draw() = 0;
  virtual void Close() = 0;

  virtual Texture2D LoadTexture2D(const char *texturePath) = 0;
  virtual void UnloadTexture2D(Texture2D texture) = 0;

  virtual Image LoadNewImage(const char *fileName) = 0;
  virtual void UnloadImage_(Image image) = 0;

  virtual Image CropImage(Image image, Rectangle rec) = 0;
  virtual Texture2D LoadTexture2DFromImage(Image image) = 0;

  virtual void SetFPS(int fps) = 0;
  virtual float GetDeltaTime() = 0;

  virtual ~Renderer() = default;
};
