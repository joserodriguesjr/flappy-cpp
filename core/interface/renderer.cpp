#include "renderer.hpp"

#ifdef DESKTOP
#include "desktop/rl_renderer.hpp"
#elif defined(ESP_PLATFORM)
#include "esp32/esp32_renderer.hpp"
#elif defined(PICO)
#include "pico/rp2040_renderer.hpp"
#endif

Renderer &Renderer::instance() {
#ifdef DESKTOP
  return RaylibRenderer::instance();
#elif defined(ESP_PLATFORM)
  return ESP32Renderer::instance();
#elif defined(PICO)
  return RP2040Renderer::instance();
#endif
}
