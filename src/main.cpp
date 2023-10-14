#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <unordered_map>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float distance(float x1, float y1, float x2, float y2) {
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

class Player : public Entity {
public:
  Player(float x, float y, float w, float h, int color, Entity *e)
      : Entity(x, y, w, h, color), eBox(e){};

  void handleInput(std::unordered_map<SDL_Keycode, bool> &keyMap) {
    for (auto const &key : keyMap) {
      if (key.first == SDLK_w && key.second) {
        this->move(0, -1 * 0.01);
      }
      if (key.first == SDLK_s && key.second) {
        this->move(0, 1 * 0.01);
      }
      if (key.first == SDLK_a && key.second) {
        this->move(-1 * 0.01, 0);
      }
      if (key.first == SDLK_d && key.second) {
        this->move(1 * 0.01, 0);
      }
    }
  }

  void update() override {
    draw_line = (distance(getX(), getY(), eBox->getX(), eBox->getY()) < 200);
  }

  void draw(SDL_Renderer *renderer) override {
    Entity::draw(renderer);
    if (draw_line) {
      SDL_SetRenderDrawColor(renderer, 0x13, 0x38, 0xBE, 255);
      SDL_RenderDrawLineF(renderer, getX(), getY(), eBox->getX(), eBox->getY());
    }
  }

private:
  bool draw_line = false;
  Entity *eBox;
};

class Box : public Entity {
public:
  Box(float x, float y, float w, float h, int color)
      : Entity(x, y, w, h, color){};
  void update() override {}
};

int main(int argc, char *argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("1b", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  bool quit = false;

  Box box(WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20, 15, 15, 0x0000FF);
  Player player(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, 20.0, 20.0, 0xFF0000,
                &box);

  std::unordered_map<SDL_Keycode, bool> keyMap;

  while (!quit) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        break;
      }
      if (e.type == SDL_KEYDOWN) {
        keyMap[e.key.keysym.sym] = true;
      }
      if (e.type == SDL_KEYUP) {
        keyMap[e.key.keysym.sym] = false;
      }
    }

    auto const &it = keyMap.find(SDLK_q);
    if (it != keyMap.end() && it->second) {
      break;
    }

    box.update();
    player.update();
    player.handleInput(keyMap);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player.draw(renderer);
    box.draw(renderer);

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
