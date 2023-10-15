#pragma once

#include "Entity.hpp"
#include <cmath>

class Box : public Entity {
public:
  Box(float x, float y, float w, float h, int color, float mass)
      : Entity(x, y, w, h, color, mass){};
  ~Box() = default;

  void update() override;

  void pull(Entity *player);
  void push(Entity *player);

private:
  float force = 0.0;
  float tx = 0.0;
  float ty = 0.0;
};
