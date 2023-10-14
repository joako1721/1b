#include "Entity.hpp"

float Entity::getX() const { return box.x + box.w / 2.0; }
float Entity::getY() const { return box.y + box.h / 2.0; }

void Entity::setX(float x) { box.x = x - box.w / 2.0; }
void Entity::setY(float y) { box.y = y - box.h / 2.0; }

void Entity::move(float x, float y) {
  box.x += x;
  box.y += y;
}
