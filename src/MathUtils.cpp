#pragma once
#include <cmath>

float distance(float x1, float y1, float x2, float y2) {
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

float normalize(float x, float maxx, float minx) {
  return (x - minx) / (maxx - minx);
}
