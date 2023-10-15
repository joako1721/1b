#include "Box.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {

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

  Box box(WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20, 15, 15, 0x0000FF, 5.0f);
  Box box2(20, 20, 15, 15, 0xFFFF00, 5.0f);
  Player player(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, 20.0, 20.0, 0xFF00FF,
                &box, 10.0);

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
    box2.update();
    player.update();
    player.handleInput(keyMap);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player.draw(renderer);
    box.draw(renderer);
    box2.draw(renderer);

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
