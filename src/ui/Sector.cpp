#include "Sector.hpp"

//const int Sector::Size = 64;
const sf::Vector2f Sector::DiagVector = sf::Vector2f(Sector::Size, Sector::Size);
const float Sector::scale = 1.f;

Sector operator+(const Sector &lhs, const Sector &rhs) {
  return Sector{lhs.x + rhs.x, lhs.y + rhs.y};
}

sf::Vector2f Sector::upperLeftPoint() const {
  return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

bool Sector::operator==(const Sector &rhs) const {
  return x == rhs.x && y == rhs.y;
}
