#include "renderer.hpp"

#ifdef DESKTOP
#include "platform/raylib/rl_renderer.hpp"
#elif defined(ESP32)
#include "platform/esp32/esp32_renderer.hpp"
#endif

Renderer &Renderer::instance() {
#ifdef DESKTOP
  return RaylibRenderer::instance();
#elif defined(ESP32)
  return ESP32Renderer::instance();
#endif
}
