#pragma once

#include "componentInterface.hpp"

struct ICParams {};

class InputComponent : public ComponentInterface {
public:
  InputComponent(ICParams p) {}
};
