#include "Player.hpp"

void Player::handleInput(std::unordered_map<SDL_Keycode, bool> &keyMap) {
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
    if (key.first == SDLK_e && key.second && draw_line) {
      this->eBox->pull(this);
    }
    if (key.first == SDLK_f && key.second && draw_line) {
      this->eBox->push(this);
    }
  }
}

void Player::update() {
  draw_line = (distance(getX(), getY(), eBox->getX(), eBox->getY()) < 200);

  if (start) {
    float dx = getX() - eBox->getX();
    float dy = getY() - eBox->getY();
    float d = distance(getX(), getY(), eBox->getX(), eBox->getY());

    // velocity should be proportional inversed to the mass of the object
    // so that the bigger object moves slower

    // mass of the object its m, my mass its m2, k its the constant
    // where if m > m2.k
    // atracting: if m < m2.k else i should fly to the object

    if (d > 0)
      eBox->move(dx / d * 0.1, dy / d * 0.1);
    if (d < 0.1 || d > 200)
      start = false;
  }
}

void Player::draw(SDL_Renderer *renderer) {
  Entity::draw(renderer);
  if (draw_line) {
    SDL_SetRenderDrawColor(renderer, 0x13, 0x38, 0xBE, 255);
    SDL_RenderDrawLineF(renderer, getX(), getY(), eBox->getX(), eBox->getY());
  }
}
