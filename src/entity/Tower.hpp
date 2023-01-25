//
// Created by Antti - on 08.12.2022.
//
#ifndef MYGAME_SRC_ENTITY_TOWER_HPP_
#define MYGAME_SRC_ENTITY_TOWER_HPP_

#include <SFML/System/Time.hpp>
#include "ui/Sector.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "SFML/System/Time.hpp"
#include <vector>
#include <memory>
#include "SFML/Audio/Sound.hpp"
/**
 * @class TowerType
 * @brief contains possible Tower types
 */
enum class TowerType {
  GunCat,
  FreezeCat,
  BombCat
};

class Tower;
using TowerPtr = std::unique_ptr<Tower>;
using Towers = std::vector<TowerPtr>;
/**
 * @class Tower
 * @brief Tower to display on the map and shoot, extends Entity class
 */
class Tower : public Entity {
 public:
  Tower(TextureHolder &textures,
        SoundBufferHolder &sounds,
        int textureID,
        Sector sector,
        int damage,
        float range,
        sf::Time shootDelay,
        int price,
        TowerType towerType);
  /**
   * @brief Update the projectile after a frame change
   * @param deltaTime Time since last frame
   * @param world Reference to World class where the projectile is displayed
   */
  void update(sf::Time deltaTime, World &world);
  /**
   * @brief Function to call when this tower is upgraded
   * @return Was the tower able to be upgraded (is there an upgrade available)
   */
  bool upgrade();
  /**
   * @brief Get this tower's range as a float value
   * @return Radius of the range as float
   */
  float getRange() const { return range; };
  /**
   * @brief Get this tower's price
   * @return Price as int
   */
  int getPrice() const { return price; }
  /**
   * @brief Get a reference to the Sector this tower is in
   * @return Reference to location Sector
   */
  const Sector &getSector() const { return sector; }
  /**
   * @brief This tower's type
   */
  TowerType type;
 private:
  bool inRange(const sf::Vector2f enemyPos, float range);
  bool upgradeable;
  std::pair<float, std::shared_ptr<Enemy>> getClosestEnemy(World &world);
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> getClosestEnemies(World &world);
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> getNeighbourEnemies(std::pair<float,
                                                                                        std::shared_ptr<Enemy>> ClosestEnemy,
                                                                              World &world);
  Sector sector;
  TextureHolder &textures_;
  SoundBufferHolder &sounds_;
  std::map<int, std::pair<int, int>> testii;
  float bombRange;
  int damage;
  float range;
  int price;
  float velocity_;
  sf::Sound soundBullet_;
  sf::Sound soundBomb_;
  sf::Sound soundSnow_;
  sf::Time shootDelay;
  sf::Time timeSinceFiring;
};

#endif //MYGAME_SRC_ENTITY_TOWER_HPP_