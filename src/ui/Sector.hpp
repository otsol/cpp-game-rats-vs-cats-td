#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <cmath>
/**
 * @struct Sector
 * @brief A Sector is a 64x64 pixel block in the game map
 * The Sector class is used to align towers properly.
 */
struct Sector {
  int x;
  int y;

  sf::Vector2f upperLeftPoint() const; //find upper left corner of a Sector
  bool operator==(const Sector &rhs) const;
  template<typename T>
  static Sector fromCoords(T xCoord, T yCoord);
  static const int Size = 64; // length of one side of a Sector
  static const sf::Vector2f DiagVector;
  static const float scale;
};

Sector operator+(const Sector &lhs, const Sector &rhs);

using Path = std::vector<Sector>;

template<typename T>
inline Sector Sector::fromCoords(T xCoord, T yCoord) {
  int xCoordMod = xCoord % 64;
  int yCoordMod = yCoord % 64;
  return Sector{static_cast<int>(xCoord - xCoordMod), static_cast<int>(yCoord - yCoordMod)};
}
