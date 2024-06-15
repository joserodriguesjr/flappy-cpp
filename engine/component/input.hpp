#pragma once

#include "component.hpp"

struct ICParams {};

class InputComponent : public ComponentInterface {
public:
  InputComponent(ICParams p) {}
};
