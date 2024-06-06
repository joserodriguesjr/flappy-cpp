#include "inputer.hpp"

#ifdef DESKTOP
#include "platform/raylib/rl_inputer.hpp"
#elif defined(ESP32)
#include "platform/esp32/esp32_inputer.hpp"
#endif

Inputer &Inputer::instance() {
#ifdef DESKTOP
  return RaylibInputer::instance();
#elif defined(ESP32)
  return ESP32Inputer::instance();
#endif
}
