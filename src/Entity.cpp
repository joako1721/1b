#include "Entity.hpp"

float Entity::getX() const { return box.x + box.w / 2.0; }
float Entity::getY() const { return box.y + box.h / 2.0; }
