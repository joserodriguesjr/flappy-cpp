#include "inputer.hpp"

#ifdef DESKTOP
#include "desktop/rl_inputer.hpp"
#elif defined(ESP_PLATFORM)
#include "esp32/esp32_inputer.hpp"
#elif defined(PICO)
#include "pico/rp2040_inputer.hpp"
#endif

Inputer &Inputer::instance() {
#ifdef DESKTOP
  return RaylibInputer::instance();
#elif defined(ESP_PLATFORM)
  return ESP32Inputer::instance();
#elif defined(PICO)
  return RP2040Inputer::instance();
#endif
}
