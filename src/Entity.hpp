#pragma once
#include <SDL2/SDL.h>

class Entity {
public:
  Entity(float x, float y, float w, float h, int color)
      : box({x, y, w, h}), color(color){};

  virtual ~Entity() = default;

  virtual void update() = 0;
  virtual void draw(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, (color & 0xFF0000) >> 16,
                           (color & 0x00FF00) >> 8, color & 0xFF, 255);
    SDL_RenderFillRectF(renderer, &box);
  }

  float getX() const;
  float getY() const;

private:
  SDL_FRect box;
  int color;
};
