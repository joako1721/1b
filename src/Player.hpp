#pragma once

#include "Box.hpp"
#include "Entity.hpp"
#include "MathUtils.hpp"
#include <SDL2/SDL.h>
#include <unordered_map>

class Player : public Entity {
public:
  Player(float x, float y, float w, float h, int color, Box *e, float mass)
      : Entity(x, y, w, h, color, mass), eBox(e){};
  ~Player() = default;

  void handleInput(std::unordered_map<SDL_Keycode, bool> &keyMap);

  void update() override;

  void draw(SDL_Renderer *renderer) override;

private:
  bool start = false;
  bool draw_line = false;
  Box *eBox;
};
