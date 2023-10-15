#include "Box.hpp"
#include "MathUtils.hpp"

#include <iostream>
#include <random>

void Box::update() {

  this->move(tx * force, ty * force);

  // linear interpolation for force to 0
  if (force > 0) 
    force =
    std::lerp(force, 0.0f, 0.001f);
  if (force < 0.001) force = 0.0f;
  //std::cout << "force: " << force << std::endl;
}

void Box::pull(Entity *player) {
  if(this->force > 0) return;
  this->force = normalize((player->getMass() / this->getMass()),10.0f, 0.01f );
  this->tx = player->getX() - this->getX();
  this->ty = player->getY() - this->getY();
  float d =
      distance(player->getX(), player->getY(), this->getX(), this->getY());

  this->tx /= d;
  this->ty /= d;
  
   
  
}

void Box::push(Entity *player) {
  if(this->force > 0) return;
  this->force = normalize((player->getMass() / this->getMass()),10.0f, 0.01f );
  this->tx = player->getX() - this->getX();
  this->ty = player->getY() - this->getY();
  float d =
      distance(player->getX(), player->getY(), this->getX(), this->getY());

  this->tx /= -d;
  this->ty /= -d;
}
